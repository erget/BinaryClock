"""
This file is part of BinaryClock.

BinaryClock is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

BinaryClock is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
BinaryClock.  If not, see <http://www.gnu.org/licenses/>.
"""

"""
A binary clock.

This package is intended as a hardware prototype with the goal of making a
binary clock out of minimal components that are each as simple as possible.
They should be able to be reorded on the fly. If you like little endian rather
than big endian, you can just turn them upside down. Each one has only a
minimal set of functions and can only be incremented. Each one knows its parent
and child in order to function intelligently, even though the single components
are stupid.

Countdown functions should also be implemented, in which the clock counts down
and by decrementing from the topmost parent. When the clock reaches 0,
something can happen. This functionality is a much lower priority than counting
up.
"""


class NegativeBinaryError(Exception):
    """A ``Binary`` cannot be less than 0."""


class MaximumValue(Exception):
    """``Binary`` cannot be incremented beyond its ``max``."""


class Binary(object):

    """A component of a binary clock."""

    def __repr__(self):
        states = [None, None]
        for i, obj in enumerate((self.parent, self.child)):
            if obj is not None:
                states[i] = obj.state
        parent_state, child_state = states
        return "Binary({}, {}, {})".format(parent_state, child_state,
                                          self.state)

    def __str__(self):
        """
        Represent ``Binary`` as big endian ``str``.

        This method traverses the chain of parents and children if necessary
        so that it is only called on the lowest child. When the lowest child
        is reached, a list is allocated to hold the return strings. It is
        instantiated with the current state and then populated recursively
        with the state of each parent, as long as parents are available. When
        the last parent has been reached, the boolean states are converted to
        ``int`` values and the list is reversed to report in big endian. The
        values in the list are joined into a string and returned.
        """
        if self.child is not None:
            return self.child.__str__()
        return_string = [self.state]
        if self.parent is not None:
            parent = self.parent
            return_string.append(parent.state)
            while parent.parent is not None:
                parent = parent.parent
                return_string.append(parent.state)
        return_string = [str(int(state)) for state in return_string]
        return_string.reverse()
        return "".join(return_string)

    def __int__(self):
        if self.child is not None:
            return self.child.__int__()
        states = [self.state] + [parent.state for parent in self._all_parents]
        decimal = 0
        while states:
            state = states.pop(-1)
            decimal += 2 ** len(states) * state
        return decimal

    def _all_relatives(self, relative_type):
        """
        Return list of all relatives of given type (either parent or child).

        Relatives are ordered by distance to ``self``.
        """
        relatives = []
        next_relative = self.__dict__[relative_type]
        while next_relative is not None:
            relatives.append(next_relative)
            next_relative = next_relative.__dict__[relative_type]
        return relatives

    @property
    def _all_parents(self):
        """Return list of all parents."""
        return self._all_relatives("parent")

    @property
    def _all_children(self):
        """Return list of all children."""
        return self._all_relatives("child")

    def __init__(self, n=0, parent=None, child=None, state=False,
                  maximum=None):
        """Increment to ``n`` if necessary, take given states and relations."""
        #: Parent ``Binary``.
        self.parent = parent
        #: Child ``Binary``.
        self.child = child
        #: Current state.
        self.state = state
        #: Maximum value
        self.max = maximum
        while n > 0:
            self.increment()
            n -= 1

    def increment(self):
        """Increment binary chain, creating parents if necessary."""
        if int(self) == max:
            raise MaximumValue("Maximum value has been reached.")
        if self.state == False:
            self.state = True
        else:
            self.state = False
            if self.parent is not None:
                self.parent.increment()
            else:
                self.parent = Binary(child=self, state=True)
        return self

    def decrement(self):
        """
        Decrement binary chain, starting at lowest child.

        If the lowest child's state is True, it is decremented. Otherwise the
        parents are traversed, decrementing when a parent with state True is
        found and setting its children to True. If the decremented parent has
        no parents, the parents are removed. If no parent can be decremented,
        a ``NegativeBinaryError`` is raised, because the binary chain is
        already at zero.
        """
        if self.child is not None:
            self.child.decrement()
        else:
            if self.state == True:
                self.state = False
            else:
                decremented = False
                parent = self.parent
                while parent is not None:
                    if parent.state == True:
                        parent.state = False
                        decremented = True
                        for child in parent._all_children:
                            child.state = True
                        if parent.parent is None:
                            parent.child.parent = None
                        parent = None
                    else:
                        parent = parent.parent
                if not decremented:
                    raise NegativeBinaryError("Countdown has reached zero.")
        return self
