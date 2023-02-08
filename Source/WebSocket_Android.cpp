#include "WebSocket_Base.h"

#include <arcana/threading/task_conversions.h>

#include <iostream>

namespace UrlLib
{

    class WebSocket::WSImpl : public WSImplBase
    {
    public:
        
        void Send(std::string message)
        {
            if (m_readyState == ReadyState::Closed  ||
                m_readyState == ReadyState::Closing ||
                m_readyState == ReadyState::Connecting)
            {
                error_callback();

                throw std::runtime_error{"WebSocket is not Open"};
            }

            try
            {
                // SEND MESSAGE
                
            }
            catch (winrt::hresult_error const& )
            {
                error_callback();
            }
        }

        void Open(std::string url,
                     std::function<void(void)> onopen,
                     std::function<void(void)> onclose,
                     std::function<void(std::string)> onmessage,
                     std::function<void(void)> onerror)
        {
            open_callback = onopen;
            close_callback = onclose;
            message_callback = onmessage;
            error_callback = onerror;

            m_url = url;

            m_readyState = ReadyState::Connecting;

            try
            {
                // INITIALIZE SOCKET
            }
            catch (hresult_error const& )
            {
                error_callback();
            }
        }

        void Close()
        {
            if (m_readyState == ReadyState::Closing ||
                m_readyState == ReadyState::Closed)
            {
                error_callback();

                throw std::runtime_error{"WebSocket is already Closing/Closed"};
            }

            m_readyState = ReadyState::Closing;

            //m_webSocket.Close();

            m_readyState = ReadyState::Closed;

            close_callback();
        }

    private:
       
        //Windows::Networking::Sockets::MessageWebSocket m_webSocket;

        std::function<void(void)> open_callback;
        std::function<void(void)> close_callback;
        std::function<void(std::string)> message_callback;
        std::function<void(void)> error_callback;
    };
}

#include "WebSocket_Shared.h"
