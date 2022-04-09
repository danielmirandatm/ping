/**
 * @file icmp.hpp
 * @author Daniel Miranda (danielmirandatm@gmail.com)
 * @brief Implementacao dos metodos da classe Socket
 * @version 0.1
 * @date 2022-04-06
 */

#include <socket.hpp>
#include <sys/time.h>


/**
 * @brief Construtor da classe Socket
 * 
 * @param dst_address endereco do servidor de destino
 * @param port porta do servidor de destino
 * @param protocol protocolo utilizado na conexao
 */
Socket::Socket(in_addr_t dst_address, unsigned short port, unsigned char protocol)
{
    int fd, ret;
    struct sockaddr_in socket_addr;
    unsigned int ttl = TTL;
    struct timeval rcv_timeout = {
        .tv_sec = RCV_TIMEOUT,
        .tv_usec = 0
    };

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = dst_address;
    socket_addr.sin_port = port;

    
    fd = socket(AF_INET, SOCK_RAW, protocol);
    if (fd < 0)
    {
        throw std::runtime_error("Erro na aquisicao do file descriptor");
    }

    ret = setsockopt(fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl));
    if (ret != 0)
    {
        throw std::runtime_error("Erro na configuracao do ttl do socket");
    }

    ret = setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&rcv_timeout, sizeof(rcv_timeout));
    if (ret != 0)
    {
        throw std::runtime_error("Erro na configuracao do timeout do recebimento de mensagem via socket");
    }

    this->socket_addr = socket_addr;
    this->socket_addr_size = sizeof(socket_addr);
    this->fd = fd;
}

/**
 * @brief Envia uma mensagem para o servidor de destino
 * 
 * @param msg_to_snd mensagem a ser enviada
 */
void Socket::snd_msg(std::vector<unsigned char> msg_to_snd)
{
    int msg_snt;

    msg_snt = sendto(this->fd, msg_to_snd.data(), msg_to_snd.size(), 0,
                    (struct sockaddr *)&this->socket_addr, this->socket_addr_size);
    
    if (msg_snt < 0)
    {
        throw std::runtime_error("Erro ao enviar mensagem via socket para o endereco de destino");
    }
}

/**
 * @brief Recebe uma mensagem do servidor de destino
 * 
 * @param msg_to_rcv mensagem a ser recebida
 */
void Socket::rcv_msg(std::array<unsigned char, MAX_SIZE_MSG_TO_RCV> *msg_to_rcv)
{
    int msg_rcvd;

    msg_rcvd = recvfrom(this->fd, msg_to_rcv->data(), msg_to_rcv->size(), 0,
                       (struct sockaddr *)&this->socket_addr, &this->socket_addr_size);
    
    if (msg_rcvd < 0)
    {
        throw std::runtime_error("Erro ao receber mensagem via socket");
    }
}

