/**
 * @file socket.hpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Header da classe socket
 * @version 0.1
 * @date 2022-04-06
 */

#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <arpa/inet.h>
#include <memory>
#include <vector>
#include <array>

#define TTL 255
#define RCV_TIMEOUT 1
#define MAX_SIZE_MSG_TO_RCV 76


class Socket
{
    public:
        /**
         * @brief Construtor da classe Socket
         * 
         * @param dst_address endereco do servidor de destino
         * @param port porta do servidor de destino
         * @param protocol protocolo utilizado na conexao
         */
        Socket(in_addr_t dst_address, unsigned short port, unsigned char protocol);

        /**
         * @brief Envia uma mensagem para o servidor de destino
         * 
         * @param msg_to_snd mensagem a ser enviada
         */
        void snd_msg(std::vector<unsigned char> msg_to_snd);

        /**
         * @brief retorna a mensagem recebida do servidor de destino
         */
        std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> rcv_msg();

    private:
        /**
         * @brief file descriptor do socket
         */
        int fd;

        /**
         * @brief configuracoes do socket
         */
        struct sockaddr_in socket_addr;

        /**
         * @brief tamanho da configuracao de socket
         */
        socklen_t socket_addr_size;
};

#endif //__SOCKET_HPP__