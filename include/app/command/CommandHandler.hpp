#ifndef GAME_CORE_APP_COMMAND_COMMAND_HANDLER_HPP
#define GAME_CORE_APP_COMMAND_COMMAND_HANDLER_HPP

#include "boost/mpl/inherit.hpp"
#include "boost/mpl/inherit_linearly.hpp"

namespace mpl = boost::mpl;

namespace GameCore {
namespace App {
namespace Command {

class BaseHandler {
 public:
  virtual ~BaseHandler() = default;
};

template <typename Command>
class Handler : public BaseHandler {
 public:
  ~Handler() override = default;

  virtual void handle(const Command& cmd) const = 0;
};

template <typename CommandTypes>
using HandlerFold = typename mpl::inherit_linearly<CommandTypes, mpl::inherit<mpl::_1, Handler<mpl::_2>>>::type;

} /* namespace Command */
} /* namespace App */
} /* namespace GameCore */

#endif
