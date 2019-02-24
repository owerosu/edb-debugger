/*
 * api.h
 *
 *  Created on: Feb 24, 2019
 *      Author: user
 */

#ifndef PLUGINS_PYTHONWRAPPER_API_H_
#define PLUGINS_PYTHONWRAPPER_API_H_
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include "edb.h"
#include "ISymbolManager.h"
#include "Symbol.h"
#include <QStringList>
namespace py = pybind11;



PYBIND11_EMBEDDED_MODULE(edbv1, m) {
    m.def("get_expression_from_user", [](std::string title,std::string msg) {
    	edb::address_t  value;
    	edb::v1::get_expression_from_user(QString::fromStdString(title),QString::fromStdString(msg),&value);
    	return value;
    });
    m.def("dump_data", (bool (*)(edb::address_t)) &edb::v1::dump_data);
    m.def("dump_data", (bool (*)(edb::address_t,bool)) &edb::v1::dump_data);

    py::class_<edb::address_t>(m, "address_t")
    	.def(py::init<unsigned long>())
		.def(py::init<edb::address_t>())
		.def("toHexString",
			[](const edb::address_t &addr) {
    			return addr.toHexString().toStdString();
    		})
		.def("toPointerString",
			[](const edb::address_t &addr,bool createdFromNativePointer) {
		    	return addr.toPointerString(createdFromNativePointer).toStdString();
		    },py::arg("createdFromNativePointer") = true)
		.def("__index__",
			[](const edb::address_t &addr) {
				return (unsigned long)addr;
			})
		.def("__int__",
			[](const edb::address_t &addr) {
				return (unsigned long)addr;
			})
		.def("__str__",
			[](const edb::address_t &addr) {
				return addr.toPointerString(true).toStdString();
			})
		.def("__add__",
			[](const edb::address_t &addr,unsigned long other) {
				return edb::address_t(addr+other);
			},py::is_operator())
		.def("__sub__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr-other);
			},py::is_operator())
		.def("__mul__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr*other);
			},py::is_operator())
		.def("__mod__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr%other);
			},py::is_operator())
		.def("__lshift__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr<<other);
			},py::is_operator())
		.def("__rshift__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr>>other);
			},py::is_operator())
		.def("__and__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr&other);
			},py::is_operator())
		.def("__xor__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr^other);
			},py::is_operator())
		.def("__or__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr|other);
			},py::is_operator())
		.def("__radd__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr+other);
			},py::is_operator())
		.def("__rsub__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(other-addr);
			},py::is_operator())
		.def("__rmul__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr*other);
			},py::is_operator())
		.def("__rmod__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(other%addr);
			},py::is_operator())
		.def("__rlshift__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(other<<addr);
			},py::is_operator())
		.def("__rrshift__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(other>>addr);
			},py::is_operator())
		.def("__rand__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr&other);
			},py::is_operator())
		.def("__rxor__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr^other);
			},py::is_operator())
		.def("__ror__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr|other);
			},py::is_operator())
		.def("__iadd__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr+other);
			},py::is_operator())
		.def("__isub__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr-other);
			},py::is_operator())
		.def("__imul__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr*other);
			},py::is_operator())
		.def("__imod__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr%other);
			},py::is_operator())
		.def("__ilshift__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr<<other);
			},py::is_operator())
		.def("__irshift__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr>>other);
			},py::is_operator())
		.def("__iand__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr&other);
			},py::is_operator())
		.def("__ixor__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr^other);
			},py::is_operator())
		.def("__ior__",
			[](const edb::address_t &addr,unsigned long other) {
				return  edb::address_t(addr|other);
			},py::is_operator());

    py::class_<ISymbolManager>(m, "symbol_manager")
		.def_static("symbols",
			[](){
				 return edb::v1::symbol_manager().symbols().toStdList();
			})
		.def_static("find",
					[](const edb::address_t address){
						 return edb::v1::symbol_manager().find(address);
					})
		.def_static("find",
					[](const std::string str){
						 return edb::v1::symbol_manager().find(QString::fromStdString(str));
					})
		.def_static("find_near_symbol",
					[](const edb::address_t address){
						 return edb::v1::symbol_manager().find_near_symbol(address);
					})
		.def_static("add_symbol",
					[](const std::shared_ptr<Symbol> address){
						 edb::v1::symbol_manager().add_symbol(address);
					})
		.def_static("clear",
					[](){
						 edb::v1::symbol_manager().clear();
					})
		.def_static("load_symbol_file",
					[](const std::string str,const edb::address_t address){
						 edb::v1::symbol_manager().load_symbol_file(QString::fromStdString(str),address);
					})
		.def_static("set_label",
					[](const edb::address_t address,const std::string str){
						 edb::v1::symbol_manager().set_label(address,QString::fromStdString(str));
					})
		.def_static("find_address_name",
					[](const edb::address_t address,bool prefixed){
						 return edb::v1::symbol_manager().find_address_name(address,prefixed).toStdString();
					},py::arg("address"),py::arg("prefixed") = true)
					/*
					 * TODO:
		.def_static("set_symbol_generator",
					[](){
						 return edb::v1::symbol_manager().set_symbol_generator(gen);
					})
					+ QHash
					*/
		.def_static("files",
					[](){
    					 std::list<std::string> list ;
    					 QStringList::const_iterator el;
    					 for(el = edb::v1::symbol_manager().files().constBegin(); el != edb::v1::symbol_manager().files().constEnd(); ++el)
						 {
    						 list.push_back((*el).toStdString());
						 }
						 return list;
					});

    py::class_<Symbol,std::shared_ptr<Symbol>>(m, "Symbol")
		.def(py::init())
		.def_property("file",
			[](const Symbol &sym){
    			return sym.file.toStdString();
			},
			[](Symbol &sym,std::string str){
				sym.file = str.c_str();
			})
		.def_property("name",
			[](const Symbol &sym){
				return sym.name.toStdString();
			},
			[](Symbol &sym,std::string str){
				sym.name = str.c_str();
			})
		.def_property("name_no_prefix",
			[](const Symbol &sym){
				return sym.name.toStdString();
			},
			[](Symbol &sym,std::string str){
				sym.name_no_prefix = str.c_str();
			})
		.def_readwrite("address",&Symbol::address)
		.def_readwrite("size",&Symbol::size)
		.def_readwrite("char",&Symbol::type)
		.def("is_code",&Symbol::is_code)
		.def("is_data",&Symbol::is_data)
		.def("is_weak",&Symbol::is_weak);

    }




#endif /* PLUGINS_PYTHONWRAPPER_API_H_ */
