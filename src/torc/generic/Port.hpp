// Torc - Copyright 2011-2013 University of Southern California.  All Rights Reserved.
// $HeadURL$
// $Id$

// This program is free software: you can redistribute it and/or modify it under the terms of the 
// GNU General Public License as published by the Free Software Foundation, either version 3 of the 
// License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
// the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License along with this program.  If 
// not, see <http://www.gnu.org/licenses/>.

#ifndef TORC_GENERIC_PORT_HPP
#define TORC_GENERIC_PORT_HPP

#include "torc/generic/PointerTypes.hpp"

//BOOST
#ifdef GENOM_SERIALIZATION
#include <boost/serialization/access.hpp>
#endif //GENOM_SERIALIZATION
#include "torc/generic/Commentable.hpp"
#include "torc/generic/Connectable.hpp"
#include "torc/generic/Extern.hpp"
#include "torc/generic/Nameable.hpp"
#include "torc/generic/PropertyContainer.hpp"
#include "torc/generic/Renamable.hpp"
#include "torc/generic/Visitable.hpp"
#include "torc/generic/Composite.hpp"
#include "torc/generic/ParentedObject.hpp"
#include "torc/generic/PortDirection.hpp"
#include "torc/generic/View.hpp"
#include "torc/generic/UserDataContainer.hpp"

namespace torc { namespace generic { class PortAttributes; } }

namespace torc {
namespace generic {

/**
 * @brief Interface for an EDIF port object
 * 
 * The Port class acts as an interface for ports in an EDIF cell. A port can be of scalar, vector
 * or bundle type. This class provides a simplified view of all three types of port. To get a
 * handle to an actual port, the client will have to use a Visitor with proper overloads of the
 * visit() function, or dynamic_cast can be used. The latter method is however not recommended. A
 * port object supports storing properties for storing different EDIF properties. See documentation
 * of the Property and PropertyContainer classes for more details.
 */
class Port : public Commentable, public Connectable, public Extern, public Nameable,
	public PropertyContainer, public Renamable, public Visitable, virtual public Composite<Port>,
	public ParentedObject<View>, public UserDataContainer {
#ifdef GENOM_SERIALIZATION
	friend class boost::serialization::access;
#endif //GENOM_SERIALIZATION
public:
	/**
	 * Get the direction of port
	 *
	 * @return Direction of port
	 */
	inline const EPortDirection getDirection() const;

	/**
	 * Set the direction of port
	 *
	 * @param[in] inSource Direction of port
	 */
	void setDirection(const EPortDirection& inSource);

	/**
	 * Get the attributes of the port. Attributes include dcFaninLoad, dcFanoutLoad_ etc.
	 *
	 * @return Pointer to PortAttributes object.
	 */
	inline const PortAttributesSharedPtr
	getAttributes() const;

	/**
	 * Set the attributes of the port. Attributes include dcFaninLoad, dcFanoutLoad_ etc.
	 *
	 * @note This method does not check whether prior set of properties exist or not. Newly set property will remove old properties.
	 *
	 * @param[in] inSource Pointer to PortAttributes object.
	 */
	void setAttributes(const PortAttributesSharedPtr& inSource);

protected:
	explicit Port();

public:
	virtual ~Port() throw ();

private:
#ifdef GENOM_SERIALIZATION
	template <class Archive> void serialize(Archive& ar, unsigned int);
#endif //GENOM_SERIALIZATION
	Port(const Port& source);

	Port& operator=(const Port& source);

	EPortDirection mDirection;
	PortAttributesSharedPtr mAttributes;
};

/**
 * Get the direction of port
 * 
 * @return Direction of port
 */
inline const EPortDirection Port::getDirection() const {
	return mDirection;
}

/**
 * Get the attributes of the port. Attributes include dcFaninLoad, dcFanoutLoad_ etc.
 * 
 * @return Pointer to PortAttributes object.
 */
inline const PortAttributesSharedPtr Port::getAttributes() const {
	return mAttributes;
}

} // namespace generic
} // namespace torc

#endif // TORC_GENERIC_PORT_HPP
