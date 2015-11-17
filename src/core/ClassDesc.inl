template <typename T>
void ClassDesc::addMember(const char* _name, T*, uint32 _address)
{
	m_members.push_back(ClassMember(_name, TYPE_REFLECTIVE, _address));
}
