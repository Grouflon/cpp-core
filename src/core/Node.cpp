#include "core/Node.h"

#include <algorithm>
#include "core/Assert.h"

Node::Node()
{
	m_parent = nullptr;
}

Node::~Node()
{
	for (auto node : m_attachedChildren)
	{
		node->unuse();
		node->m_parent = nullptr;
	}

	for (auto node : m_children)
	{
		node->unuse();
		node->m_parent = nullptr;
	}
}

void Node::detachChild(Node* _node)
{
#ifdef _DEBUG
	ASSERT(std::find(m_children.begin(), m_children.end(), _node) != m_children.end());
#endif

	m_detachedChildren.push_back(_node);
}

void Node::attachChild(Node* _node)
{
#ifdef _DEBUG
	ASSERT(std::find(m_children.begin(), m_children.end(), _node) == m_children.end());
	ASSERT(std::find(m_attachedChildren.begin(), m_attachedChildren.end(), _node) == m_attachedChildren.end());
#endif

	m_attachedChildren.push_back(_node);
	_node->use();

	if (_node->m_parent != nullptr)
	{
		_node->m_parent->detachChild(_node);
	}
}

void Node::updateDetachedList()
{
	for (auto node : m_children)
	{
		node->updateDetachedList();
	}

	for (auto node : m_detachedChildren)
	{
		auto it = std::find(m_children.begin(), m_children.end(), node);
		if (it != m_children.end())
		{
			m_children.erase(it);
			node->unuse();
			node->m_parent = nullptr;
		}
	}
	m_detachedChildren.clear();
}

void Node::updateAttachedList()
{
	for (auto node : m_attachedChildren)
	{
		m_children.push_back(node);
		node->m_parent = this;
	}
	m_attachedChildren.clear();

	for (auto node : m_children)
	{
		node->updateAttachedList();
	}
}

Node* Node::getParent() const
{
	return m_parent;
}

const std::vector<Node*>& Node::getChildren() const
{
	return m_children;
}

void Node::setName(const char* _value)
{
	m_name = _value;
}

const char* Node::getName() const
{
	return m_name.c_str();
}

void Node::setTranslation(float _x, float _y, float _z)
{
	m_transform.setTranslation(_x, _y, _z);
}

void Node::setTranslation(const glm::vec3& _v)
{
	m_transform.setTranslation(_v);
}

glm::vec3 Node::getTranslation() const
{
	return m_transform.getTranslation();
}

void Node::setRotation(float _i, float _j, float _k, float _w)
{
	m_transform.setRotation(_i, _j, _k, _w);
}

void Node::setRotation(glm::quat& _q)
{
	m_transform.setRotation(_q);
}

glm::quat Node::getRotation() const
{
	return m_transform.getRotation();
}

void Node::setScale(float _x, float _y, float _z)
{
	m_transform.setScale(_x, _y, _z);
}

void Node::setScale(const glm::vec3& _v)
{
	m_transform.setScale(_v);
}

glm::vec3 Node::getScale() const
{
	return m_transform.getScale();
}

glm::mat4 Node::getLocalMatrix() const
{
	return m_transform.getLocalMatrix();
}

glm::mat4 Node::getWorldMatrix() const
{
	return m_transform.getWorldMatrix();
}