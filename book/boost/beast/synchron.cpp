#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/websocket.hpp>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/websocket/stream.hpp>
#include <iostream>
#include <string>

#define HOST "app.localhost"
#define PORT "8070"
#define PATH "/pc/chat"

using std::cout;
using std::endl;

// Подключение пространств имен
namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;

using tcp = asio::ip::tcp;


int main() {
  
  asio::io_context ioc;

  
  // Превращаем имя в IP адрес (резолвим)
  tcp::resolver resolver(ioc);
  auto const results = resolver.resolve(HOST,PORT);
  
  // Создаем websocket поток (умный поток для работы с обычным сокетом) 
  websocket::stream<tcp::socket> ws(ioc);
  
  // Подключаем базовый tcp сокет для первоначальных функций
  asio::connect(beast::get_lowest_layer(ws),results);
  
  // Тут мы пытаемся подключится к опредленному endpoint веб-сокет сервера 
  ws.handshake(HOST,PATH);
  
  cout << "Успешно подключено: " << HOST << endl;
  
  // Отправляем данные 
  ws.write(asio::buffer(std::string("Привет сервер")));
  
  // Получения ответа
  beast::flat_buffer buffer; // специальный саморасширающийся умный буфер
  ws.read(buffer);
  
  //                             делаем данные в буфере строкой 
  cout << "Ответ от сервера: " << beast::make_printable(buffer.data()) << endl;
  

  // Закрытие сервера 
  ws.close(websocket::close_code::normal);

  ioc.run();
  
  return 0;
}
