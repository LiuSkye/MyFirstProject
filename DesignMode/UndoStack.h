/*
 * @Author: Skye
 * @Date: 2021-07-14 16:35:00
 * @LastEditTime: 2021-07-15 17:14:52
 * @Description: 撤销重做栈
 * Skye:'Never stop!'
 */
#pragma once

#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <functional>
#include <mutex>
#include <assert.h>

// 记录状态的节点：如xml节点
class UndoRedoStack;
class ProjectNode
{
public:
    bool AddData(const std::string &str = "A")
    {
        //_data.append(str);
        _data += "A";
        return true;
    }
    bool DeleteData(const std::string &str = "A")
    {
        _data.pop_back();
        return true;
    }
    bool ModifyData(int pos, char c)
    {
        _data.back() = 'C';
        return true;
    }

    // 假设用string存储着数据
    std::string _data;
};

// 动作类型
enum ActionType
{
    Action_ADD = 0,
    Action_DELETE,
    Action_Modify,
    Action_Move,

    Action_Other
};

// 命令模式实现
// 动作类型
class Action
{
public:
    Action(ActionType type, int id, const std::string &desc, std::shared_ptr<ProjectNode> obj, const std::function<bool()> &command)
        : _type(type),_id(id), _description(desc), _object(obj), _command(command) {}
    virtual ~Action(){};

    bool Excute()
    {
        return _command();
    }
    ActionType _type;
    int _id;
    std::string _description;

    std::shared_ptr<ProjectNode> _object;
    std::function<bool()> _command;
    std::string _data;
};

class UndoRedoStack
{
public:
    UndoRedoStack()
        : _max_act_size(20),
          _undoPos(-1),
          _is_in_act(false),
          _act_id(-1)
    {
    }
    virtual ~UndoRedoStack() {}

public:
    void SetMaxActSize(int size)
    {
        if (size < 1)
            return;
        _max_act_size = size;
    }

    // 开始一个命令
    void BeginAnAction(std::string desc, std::shared_ptr<Action> act)
    {
        if (IsInAction())
        {
            assert(!"UndoRedoStack: 前一个命令尚未结束！");
            return;
        }
        _is_in_act = true;
        _act_id = CreateUniqueId();
        _act_description = desc;
    }

    void EndAnAction(const std::string &desc = "") //非常量引用的初始值必须为左值，常量引用是万能引用，可以用右值初始化
    {
        if (IsInAction())
        {
            _is_in_act = false;
            if (!_act_description.empty())
            {
                for (int i = (int)_actionStack.size() - 1; i >= 0; --i)
                {
                    // 将这一动作包含的全部命令更改为命令结束描述
                    std::shared_ptr<Action> act = _actionStack[i];
                    if (act->_id != _act_id)
                        break;

                    act->_description = _act_description;
                }
            }
        }
    }

    bool Undo()
    {
        if (IsInAction())
        {
            assert(!"UndoRedoStack: 正在命令动作中，不应撤销重做！");
            EndAnAction();
        }
        if (_undoPos <= 0) //已经撤销到底了
        {
            return false;
        }
        else if (_undoPos > _actionStack.size())
        {
            assert(!"严重错误！");
            _undoPos = (int)_actionStack.size();
            return false;
        }
        const int act_id = _actionStack[_undoPos - 1]->_id;
        for (int index = _undoPos - 1; index >= 0; --index)
        {
            std::shared_ptr<Action> act = _actionStack[index];
            if (act->_id != act_id)
            {
                // 回撤结束
                break;
            }

            if (act->Excute())
            {
                --_undoPos;
                return true;
            }
            else
                return false;
            // bool rtvalue = false;
            // switch (act->_type)
            // {
            // case Action_ADD:
            //     break;
            // case Action_DELETE:
            //     break;
            // case Action_Modify:
            //     break;
            // case Action_Move:
            //     break;
            // default:
            //     rtvalue = ;
            //     break;
            // }
        }
        return true;
    }

    bool Redo()
    {
        if (IsInAction())
        {
            assert(!"UndoRedoStack: 正在命令动作中，不应撤销重做！");
            EndAnAction();
        }
        if (_undoPos < 0)
        {
            return false;
        }
        else if (_undoPos >= _actionStack.size())
        {
            assert(!"严重错误！");
            _undoPos = (int)_actionStack.size();
            return false;
        }
        const int act_id = _actionStack[_undoPos]->_id;
        for (int index = _undoPos; index < _actionStack.size(); ++index)
        {
            auto act = _actionStack[index];
            if (act->_id != act_id)
            {
                break;
            }
            if(act->_type == Action_ADD)
            {
                act->_object->AddData();
                ++_undoPos;
                return true;
            }
            else if(act -> _type == Action_DELETE){
                act->_object->DeleteData();
                ++_undoPos;
                return true;
            }
            else
                return false;
        }
        return true;
    }

    void Push(const std::shared_ptr<Action> &act)
    {
        _actionStack.push_back(act);
        ++_undoPos;
        if (_actionStack.size() > _max_act_size)
        {
            _actionStack.pop_front();
            --_undoPos;
        }
    }

public:
    bool (ProjectNode::*ptr)(const string&) = &ProjectNode::DeleteData;
    void ActionAddNode(std::shared_ptr<ProjectNode> node)
    {
        std::shared_ptr<Action> act(new Action(Action_ADD, CreateUniqueId(), "Add", node, std::bind(ptr, node , "A")));
        Push(act);
    }
    void ActionDeleteNode(std::shared_ptr<ProjectNode> node)
    {
        std::shared_ptr<Action> act(new Action(Action_ADD, CreateUniqueId(), "Delete", node, std::bind(ptr, node, "A")));
        Push(act);
    }

    void ClearStack() { _actionStack.clear(); }

private:
    bool IsInAction()
    {
        return _is_in_act;
    }

    int CreateUniqueId()
    {
        return _actionStack.empty() ? 0 : _actionStack.back()->_id + 1;
    }

private:
    std::deque<std::shared_ptr<Action>> _actionStack;
    mutable std::mutex _mutex_stack;
    int _max_act_size;
    int _undoPos;
    bool _is_in_act;
    int _act_id;
    std::string _act_description;

    //int _last_save_pos;
};