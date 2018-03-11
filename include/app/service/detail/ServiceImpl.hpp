#ifndef GAME_CORE_APP_SERVICE_DETAIL_SERVICE_IMPL_HPP
#define GAME_CORE_APP_SERVICE_DETAIL_SERVICE_IMPL_HPP

#include <memory>
#include <utility>

#include "boost/mpl/for_each.hpp"

#include "app/command/CommandHandler.hpp"

namespace GameCore {
namespace App {
namespace Service {
namespace Detail {

template <typename Commands>
class ServiceImpl : public Command::HandlerFold<Commands> {
 public:
  //! Friend factory function to create a service registered on the given dispatcher.
  template <typename ServiceType, typename... Args>
  friend std::shared_ptr<ServiceType> makeRegistered(Args&&... args);

  template <typename Dispatcher>
  void registerCommandHandlers(Dispatcher& dispatcher, const std::shared_ptr<ServiceImpl>& service) const {
    mpl::for_each<Commands, std::add_pointer<mpl::_1>>([&dispatcher, &service](auto c) {
      using CommandType = std::remove_pointer_t<decltype(c)>;

      dispatcher.template registerHandler<CommandType>(service);
    });
  }
};

template <typename ServiceType, typename Dispatcher, typename... Args>
std::shared_ptr<ServiceType> makeRegistered(Dispatcher& dispatcher, Args&&... args) {
  auto service = std::make_shared<ServiceType>(std::forward<Args>(args)...);
  service->registerCommandHandlers(dispatcher, service);
  return service;
}

} /* namespace Detail */
} /* namespace Service */
} /* namespace App */
} /* namespace GameCore */

#endif
