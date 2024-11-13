#pragma once

enum class FoodType
{
	None,
	BREAD = 1,
	PATTY,
	CHEESE,
	LETTUCE,
	TOMATO,
	P,	//patty burger
	L,	//lettuce burger
	PL,	//patty&lettuce burger
	C,	//cheese burger
	CL,	//cheese&lettuce burger
	CP,	//cheese&patty burger
	CLP, //cheese&lettuce&patty burger
	T,	//tomato burger
	PT, //patty&tomato burger
	LT, //lettuce&tomato burger
	CT, //cheese&tomato burger
	PLT, //patty&lettuce&tomato burger
	PCT, //patty&cheese&tomato burger
	LCT, //lettuce&cheese&tomato burger
	PLCT, //patty&lettuce&cheese&tomato burger
	COKE,
	FRENCHFRIES,
	ICECREAM,
	Count
};