/*
 * api.h
 *
 *  Created on: Feb 24, 2019
 *      Author: user
 */

#ifndef PLUGINS_PYTHONWRAPPER_API_H_
#define PLUGINS_PYTHONWRAPPER_API_H_
#include <pybind11/pybind11.h>

PYBIND11_EMBEDDED_MODULE(edbv1, m) {
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


#endif /* PLUGINS_PYTHONWRAPPER_API_H_ */
