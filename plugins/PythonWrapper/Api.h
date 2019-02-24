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
#include "edb.h"

namespace py = pybind11;


PYBIND11_EMBEDDED_MODULE(edbv1, m) {
    m.def("get_expression_from_user", [](std::string title,std::string msg) {
    	edb::address_t  value;
    	edb::v1::get_expression_from_user(QString::fromStdString(title),QString::fromStdString(msg),&value);
    	return value;
    });
    m.def("dump_data", [](edb::address_t addr) {
    	edb::v1::dump_data(addr);
    	return;
    });
    m.def("dump_data", [](edb::address_t addr,bool new_tab) {
    	edb::v1::dump_data(addr,new_tab);
    	return;
    });
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
			},py::is_operator())
;
    }




#endif /* PLUGINS_PYTHONWRAPPER_API_H_ */
