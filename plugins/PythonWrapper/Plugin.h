#ifndef MYPLUGIN_H_
#define MYPLUGIN_H_
#include <pybind11/embed.h>
#include "IPlugin.h"


class QPlainTextEdit;
class QLineEdit;

// we wrap everything in a namespace, this way we don't conflict with
// symbols from other plugins or edb itself
namespace PythonWrapper {

// inherit from both QObject and IPlugin
class PythonWrapper : public QObject, public IPlugin {
    // some requisite meta-data
    Q_OBJECT
    Q_INTERFACES(IPlugin)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "edb.IPlugin/1.0")
#endif
    Q_CLASSINFO("author", "Owerosu")
    Q_CLASSINFO("url", "https://github.com/owerosu/")

public:
    PythonWrapper();
    virtual ~PythonWrapper() override;
    void bridgePrint(std::string str);
    void bridgePrintInput(std::string str);
    QLineEdit* lineWidget();
public:
    virtual QMenu *menu(QWidget *parent = nullptr) override;
public Q_SLOTS:
    void runScript();
    void lineSent();
	void resetInterpreter();
	void loadScript();
private:
    QMenu *menu_ = nullptr;
    QPlainTextEdit* textWidget_ = nullptr;
    QLineEdit* lineWidget_ = nullptr;
	pybind11::scoped_interpreter *interpreter_ = nullptr;
	void initInterpreter();
	void displayError(const char*);
};

}

#endif
