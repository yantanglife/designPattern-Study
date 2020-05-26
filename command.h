#pragma once
#include <iostream>
#include <list>
#include <deque>
#include <string>

namespace command {

// ������
class Receiver {
public:
    void action();
};

// ���������
class Command {
public:
    Command() {}
    // �ù��캯�� �� setReceiver() ����  m_receiver
    Command(Receiver* receiver) : m_receiver(receiver) {}
    void setReceiver(Receiver* receiver) { m_receiver = receiver; }
    virtual void execute() = 0;
protected:
    Receiver* m_receiver;
};

class ConcreteCommand : public Command {
public:
    ConcreteCommand() {}
    ConcreteCommand(Receiver* receiver) { m_receiver = receiver; }
    // ֪ͨ �����ߣ������� Receiver::Action()
    void execute();
};

// �����ߣ�����������
class Invoker {
public:
    // ���� ����
    void setCommand(Command* command);
    // 
    void notify();
private:
    std::list<Command*> m_commands;
};


// 
void Receiver::action() {
    std::cout << "Receiver::action()." << std::endl;
}

void ConcreteCommand::execute() {
    m_receiver->action();
}

void Invoker::setCommand(Command* pCommand) {
    m_commands.push_back(pCommand);
}

void Invoker::notify() {
    for (auto it = m_commands.begin(); it != m_commands.end(); ++it) {
        (*it)->execute();
    }
}


void commandTest() {
    Receiver* pReceiver = new Receiver();
    Command* pCommand = new ConcreteCommand();
    pCommand->setReceiver(pReceiver);
    Invoker* pInvoker = new Invoker();
    pInvoker->setCommand(pCommand);
    pInvoker->notify();

    delete pReceiver;
    delete pCommand;
    delete pInvoker;
}

}


namespace command_imp {

// ʵ�ּ�����ĳ����ͻָ�

class Receiver;

// ���������࣬����ľ��������Ҫ���������ߴ���
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// �ӷ�����
class AddCommand : public Command {
public:
    AddCommand(Receiver* receiver, int operand) 
        : m_receiver(receiver), m_operand(operand) {}
    void execute();
    void undo();
private:
    int m_operand;
    Receiver* m_receiver;
};

// ��������
class SubCommand : public Command {
public:
    SubCommand(Receiver* receiver, int operand)
        : m_receiver(receiver), m_operand(operand) {}
    void execute();
    void undo();
private:
    int m_operand;
    Receiver* m_receiver;
};

// ������
class Receiver {
public:
    Receiver() : m_value(0) {}

    void add(int operand) { m_value += operand; }
    void sub(int operand) { m_value -= operand; }
    int getValue() { return m_value; }
private:
    int m_value;
};


class Invoker {
public:
    Invoker(int length) : m_maxCommandsLength(length) {}
    ~Invoker() {}

    void undoCommand();
    void redoCommand();
    void excuteCommand(Command*);
private:
    // ��ʷ��¼�б�. ���������б���󳤶ȣ�ʹ�� deque ���� stack.
    std::deque<Command*> m_undoCommands;
    std::deque<Command*> m_redoCommands;
    int m_maxCommandsLength;
};

// ִ��������洢����
void Invoker::excuteCommand(Command* pCommand) {
    // �����ɴ�ŵ�����������ɾ��һ�������
    if (m_undoCommands.size() >= m_maxCommandsLength) {
        m_undoCommands.pop_front();
    }
    m_undoCommands.push_back(pCommand);
    pCommand->execute();
}
// ��������
void Invoker::undoCommand() {
    std::cout << "Undo~";
    if (m_undoCommands.size() > 0) {
        Command* pCommand = m_undoCommands.back();
        pCommand->undo();
        m_undoCommands.pop_back();
        
        if (m_redoCommands.size() >= m_maxCommandsLength) {
            m_redoCommands.pop_front();
        }
        m_redoCommands.push_back(pCommand);
    }
    else {
        std::cout << "Undo list empty." << std::endl;
    }
}
// �ָ�
void Invoker::redoCommand() {
    std::cout << "Redo~";
    if (m_redoCommands.size() > 0) {
        Command* pCommand = m_redoCommands.back();
        // �ָ�������ִ�и�����
        pCommand->execute();
        m_redoCommands.pop_back();
        
        if (m_undoCommands.size() >= m_maxCommandsLength) {
            m_undoCommands.pop_front();
        }
        m_undoCommands.push_back(pCommand);
    }
    else {
        std::cout << "Redo list empty." << std::endl;
    }
}


void AddCommand::execute() {
    std::cout << "AddCommand: "<< m_receiver->getValue() << " + " << m_operand << " = ";
    m_receiver->add(m_operand);
    std::cout << m_receiver->getValue() << std::endl;
}
void AddCommand::undo() {
    m_receiver->sub(m_operand);
    std::cout << m_receiver->getValue() << std::endl;
}

void SubCommand::execute() {
    std::cout << "SubCommand: " << m_receiver->getValue() << " - " << m_operand << " = ";
    m_receiver->sub(m_operand);
    std::cout << m_receiver->getValue() << std::endl;
}
void SubCommand::undo() { 
    m_receiver->add(m_operand);
    std::cout << m_receiver->getValue() << std::endl;
}


// Test
void commandImpTest() {
    Receiver* pReceiver = new Receiver();
    Invoker* pInvoker = new Invoker(2);

    Command* pCommand = new AddCommand(pReceiver, 10);
    pInvoker->excuteCommand(pCommand);
    
    pInvoker->redoCommand();

    Command* pCommand1 = new AddCommand(pReceiver, 22);
    pInvoker->excuteCommand(pCommand1);
    Command* pCommand2 = new SubCommand(pReceiver, 30);
    pInvoker->excuteCommand(pCommand2);
    pInvoker->undoCommand();
    pInvoker->redoCommand();
    pInvoker->undoCommand();
    pInvoker->undoCommand();
    pInvoker->undoCommand();
    pInvoker->excuteCommand(pCommand1);

}

}
