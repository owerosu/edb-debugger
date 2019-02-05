#include <Python.h> // Must be" first, see https://stackoverflow.com/questions/15078060/embedding-python-in-qt-5
#include "Plugin.h"
#include "edb.h"
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QEventLoop>
#include <QMainWindow>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/eval.h>
#include <string>
namespace PythonWrapper {

QString helperColoredString(QString color, QString msg){
	QString coloredText ;
	coloredText.append("<font color=\"");
	coloredText.append(color);
	coloredText.append("\">");
	coloredText.append(msg);
	coloredText.append("</font>");
	return coloredText;
}

PythonWrapper* instance = nullptr;

bool IS_WAITING_TEXT_INPUT = false;

PYBIND11_EMBEDDED_MODULE(bridge, m) {
    // `m` is a `py::module` which is used to bind functions and classes
    m.def("print", [](std::string str) {
    	instance->bridgePrint(str);
    });
    m.def("input", []() {
        QEventLoop loop;
        QObject::connect(instance->lineWidget(), SIGNAL(returnPressed()), &loop, SLOT(quit()));
        IS_WAITING_TEXT_INPUT = true;
        loop.exec();
        auto ligne = instance->lineWidget()->text().toStdString();
        instance->bridgePrintInput(ligne);
        instance->lineWidget()->setText("");
        IS_WAITING_TEXT_INPUT = false;
        return ligne;
    });

}
PYBIND11_EMBEDDED_MODULE(edb, m) {
    m.def("get_expression_from_user", [](std::string title,std::string msg) {
    	edb::address_t  value;
    	edb::v1::get_expression_from_user(QString::fromStdString(title),QString::fromStdString(msg),&value);
    	return (unsigned long)value;
    });
    m.def("dump_data", [](unsigned long addr) {
    	edb::v1::dump_data(addr);
    	return;
    });
}
// Skeleton taken from DebuggerErrorConsole plugin
PythonWrapper::PythonWrapper() : menu_(nullptr) {
	//Py_Initialize();
	instance = this;
	textWidget_ = new QPlainTextEdit;
	textWidget_->setReadOnly(true);
	QFont font("monospace");
	font.setStyleHint(QFont::TypeWriter);
	textWidget_->setFont(font);
	textWidget_->setWordWrapMode(QTextOption::WrapMode::NoWrap);
	textWidget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	//qInstallMessageHandler(debugMessageIntercept);

	lineWidget_ = new QLineEdit;
	lineWidget_->setFont(font);
    connect(lineWidget_, SIGNAL(returnPressed()),this, SLOT(lineSent())); // FIXME: Works only with numpad key as the event is caught somewhere else
}

PythonWrapper::~PythonWrapper() {
}
QLineEdit* PythonWrapper::lineWidget(){
	return lineWidget_;
}
void PythonWrapper::initInterpreter(){
	if(interpreter_) // Reset if already initialized
	{
		delete interpreter_;
	}
	interpreter_ = new pybind11::scoped_interpreter;
	textWidget_->setPlainText("");
	std::string stdOutErr = // inspired from https://stackoverflow.com/questions/46632488/how-to-catch-python-3-stdout-in-c-code
    "import bridge\n"
	"def _print(txt):\n"
	"    bridge.print(str(txt))\n"
	"def _input(txt=None):\n"
	"    if txt:\n"
	"        bridge.print(str(txt))\n"
	"    return bridge.input()\n"
	"__builtins__.print=_print\n"
	"__builtins__.input=_input\n";
	pybind11::exec(stdOutErr);
}
QMenu *PythonWrapper::menu(QWidget *parent) {
	if(!menu_) {
		initInterpreter();
		if(auto mainWindow = qobject_cast<QMainWindow *>(edb::v1::debugger_ui)) {
			auto dockWidget = new QDockWidget(tr("Python console"), mainWindow);
			dockWidget->setObjectName(QString::fromUtf8("Python console"));
			auto layout = new QVBoxLayout;
			auto widget = new QWidget;
			layout->addWidget(textWidget_);
			layout->addWidget(lineWidget_);
			widget->setLayout(layout);
			dockWidget->setWidget(widget);

			mainWindow->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

			menu_ = new QMenu(tr("Python Script"), parent);
			menu_->addAction(dockWidget->toggleViewAction());
			menu_->addAction(tr("Reset interpreter"),this,SLOT(resetInterpreter()));
			menu_->addAction(tr("Run script"),this,SLOT(loadScript()));

			auto docks = mainWindow->findChildren<QDockWidget *>();

			// We want to put it to the same area as Stack dock
			// Stupid QList doesn't have a reverse iterator
			for(auto it = docks.end() - 1 ;; --it) {
				QDockWidget *const widget = *it;

				if(widget != dockWidget && mainWindow->dockWidgetArea(widget) == Qt::BottomDockWidgetArea) {
					mainWindow->tabifyDockWidget(widget, dockWidget);
					widget->show();
					widget->raise();
					break;
				}

				if(it == docks.begin()) {
					break;
				}
			}

		}
	}
	return menu_;
}
void PythonWrapper::bridgePrint(std::string str){
	textWidget_->appendPlainText(QString::fromStdString(str));
}
/* Display value expected by input() in another color for visibility */
void PythonWrapper::bridgePrintInput(std::string str){
	textWidget_->appendHtml(helperColoredString(QString("blue"),QString::fromStdString(str)));
}
void PythonWrapper::lineSent(){
	if(!IS_WAITING_TEXT_INPUT)
	{
		auto command = lineWidget_->text();
		textWidget_->appendPlainText(">>> "+command);
		lineWidget_->setText("");
		try{
			pybind11::exec(command.toStdString());
		}
		catch(pybind11::error_already_set &e)
		{
			displayError(e.what());
		}
	}
}
void PythonWrapper::displayError(const char* str){
	textWidget_->appendHtml(helperColoredString(QString("red"),str));
}
void PythonWrapper::runScript() {
    QMessageBox::information(0, tr("Not implemented"), tr("Not implemented"));
}
void PythonWrapper::resetInterpreter() {
	initInterpreter();
}
void PythonWrapper::loadScript() {
	QString file = QFileDialog::getOpenFileName(edb::v1::debugger_ui,tr("Open a python script:"),QDir::homePath(),tr("Python Script (*.py)"));
	initInterpreter();
	QDir parent = QFileInfo(file).dir(); // Retrieve parent directory to initialize correct python path
	pybind11::exec("import sys");
	pybind11::exec(std::string("sys.path.append('")+parent.absolutePath().toStdString()+std::string("')"));
	try{
		pybind11::eval_file(file.toStdString());
	}
	catch(pybind11::error_already_set &e)	{
		displayError(e.what());
	}
}
}
