#pragma once

#include <vector>

#include "core/Resource.h"
#include "core/Transform.h"

class Node : public Resource
{
public:
	Node();
	virtual ~Node();

	void detachChild(Node* _node);
	void attachChild(Node* _node);
	void updateDetachedList();
	void updateAttachedList();

	Node* getParent() const;
	const std::vector<Node*>& getChildren() const;

	void		setName(const char* _value);
	const char* getName() const;

	void		setTranslation(float _x, float _y, float _z);
	void		setTranslation(const glm::vec3& _v);
	glm::vec3	getTranslation() const;
	void		setRotation(float _i, float _j, float _k, float _w);
	void		setRotation(glm::quat& _q);
	glm::quat	getRotation() const;
	void		setScale(float _x, float _y, float _z);
	void		setScale(const glm::vec3& _v);
	glm::vec3	getScale() const;
	glm::mat4	getLocalMatrix() const;
	glm::mat4	getWorldMatrix() const;

private:
	std::string	m_name;
	Transform	m_transform;

	Node* m_parent;

	std::vector<Node*> m_children;
	std::vector<Node*> m_attachedChildren;
	std::vector<Node*> m_detachedChildren;
};