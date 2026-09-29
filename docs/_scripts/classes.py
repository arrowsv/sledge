from dataclasses import dataclass, field
from typing import List

@dataclass
class ParameterDoc:
    name: str = ""
    type: str = ""
    description: str = ""
    optional: bool = False
    fields: List["ParameterDoc"] = field(default_factory=list)

@dataclass
class ReturnDoc:
    name: str = "result"
    type: str = ""
    description: str = ""

@dataclass
class FunctionDoc:
    name: str = ""
    description: str = ""
    parameters: List[ParameterDoc] = field(default_factory=list)
    returns: List[ReturnDoc] = field(default_factory=list)
    qualified_name: str = ""

@dataclass
class FieldDoc:
    name: str = ""
    type: str = ""
    description: str = ""
    qualified_name: str = ""

@dataclass
class TypeDoc:
    name: str = ""
    inherits: str = ""
    methods: List[FunctionDoc] = field(default_factory=list)
    functions: List[FunctionDoc] = field(default_factory=list)
    fields: List[FieldDoc] = field(default_factory=list)

@dataclass
class DefineDoc:
    name: str = ""
    fields: List[FieldDoc] = field(default_factory=list)

@dataclass
class NamespaceDoc:
    name: str = ""
    functions: List[FunctionDoc] = field(default_factory=list)
    fields: List[FieldDoc] = field(default_factory=list)

@dataclass 
class EventDataDoc:
    name: str = ""
    type: str = ""
    description: str = ""

@dataclass
class EventDoc:
    name: str = ""
    description: str = ""
    data: List[EventDataDoc] = field(default_factory=list)