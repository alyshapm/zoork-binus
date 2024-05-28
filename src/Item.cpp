#include "Item.h"
#include "NullCommand.h"
#include <utility>
#include <memory>

Item::Item(const std::string &n, const std::string &d) : GameObject(n, d),
                                                         useCommand(std::make_shared<NullCommand>()) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : GameObject(n, d),
                                                                                     useCommand(std::move(c)) {}

void Item::use() {
    if (useCommand) {
        useCommand->execute();
    } else {
        std::cout << "You can't use that.\n";
    }
}

void Item::setUseCommand(std::shared_ptr<Command> c) {
    useCommand = c;
}