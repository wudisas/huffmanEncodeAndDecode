
all : HEncode HDecode

HEncode : hEncode.cc simon_func.cc
	g++-5 -std=c++14 -o HEncode hEncode.cc simon_func.cc

HDecode : HDecode.cc simon_func.cc
	g++-5 -std=c++14 -o HDecode HDecode.cc simon_func.cc
