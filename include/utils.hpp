/**
 * @file utils.hpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Header das funcoes utilitarias
 * @version 0.1
 * @date 2022-04-06
 */

#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <arpa/inet.h>


/**
 * @brief Retorna o endereco IP resolvido a partir do endereco de destino escolhido
 * 
 * @param dst_address endereco de destino escolhido pelo usuario
 * @return in_addr_t 
 */
in_addr_t get_ip_by_hostname(const char *dst_address);

#endif //__UTILS_HPP__