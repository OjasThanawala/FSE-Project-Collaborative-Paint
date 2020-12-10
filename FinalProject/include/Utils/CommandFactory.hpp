/**
 *  @file   CommandFactory.hpp
 *  @brief  Stores every type of Command.
 *  @author Valgrind Warriors
 *  @date   2020-12-08
 ***********************************************/

#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP

class App;
class Command;
class CommandPacket;

class CommandFactory{
    private:
    App *m_app;

    public:
        // Constructor
        explicit CommandFactory(App *app) : m_app(app) {};
        // function to create command
        void getCommand(CommandPacket *);
};

#endif //APP_COMMANDFACTORY_HPP
