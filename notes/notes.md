//1 
//funzione prende
//-LuaState, 
//-stringa che diventera il nome della global
//-funzione che inizializza la libreria
//-glb: If glb is true, also stores the result into global modname.
luaL_requiref(m_L, "MyLib", luaopen_MyLib, 1); // Stack: MyLib

//2
int luaopen_MyLib(lua_State *L) {

	//3
	static const luaL_Reg MyLib_lib[] = {
		{ "MakeObj", &MyLib_MakeObj },
		{ NULL, NULL }
	};

	static const luaL_Reg Obj_lib[] = {
		{ "method", &Obj_method },
		{ NULL, NULL }
	};	

	//4 Creates a new table and registers there the functions in array
	luaL_newlib(L, MyLib_lib); // Stack: "MyLib" table(MyLib_lib)

	//5 If the registry already has the key tname, returns 0. 
	//	Otherwise, creates a new table to be used as a metatable for userdata, adds it to the registry with key tname, and returns 1.
	//  In both cases pushes onto the stack the final value associated with tname in the registry.
	luaL_newmetatable(L, Obj_typename); // Stack: "MyLib" table(MyLib_lib) table(metatable)

	luaL_newlib(L, Obj_lib); // Stack: "MyLib" table(MyLib_lib) table(metatable) table(Obj_lib)
	
	//7 Does the equivalent to t["__index"] = v, where t is the value at the given index and v is the value at the top of the stack.
	//	This function pops the value from the stack.
	//	Quindi in pratica Obj_lib diventa la meta di metatable
	lua_setfield(L, -2, "__index"); // Stack: "MyLib" table(MyLib_lib) table(metatable)

	//8
	lua_pushstring(L, "__gc"); // Stack: "MyLib" table(MyLib_lib) table(metatable) "__gc"

	//9
	lua_pushcfunction(L, Obj__gc); // Stack: "MyLib" table(MyLib_lib) table(metatable) "__gc" function(Obj_gc)
	
	//10
	// Does the equivalent to t[k] = v, 
	// where t is the value at the given index, 
	// v is the value at the top of the stack, 
	// and k is the value just below the top.
	// This function pops both the key and the value from the stack. As in Lua,
	lua_settable(L, -3); // Stack: "MyLib" table(MyLib_lib) table(metatable)

	//11
	lua_pop(L, 1); // Stack: "MyLib" table(MyLib_lib)
