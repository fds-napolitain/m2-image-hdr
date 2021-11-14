//
// Created by Maxime Boucher on 14/11/2021.
//

#ifndef QTHDR_PIPELINE_HPP
#define QTHDR_PIPELINE_HPP


enum class Align {
	NONE,
	MTB,
};

enum class Merge {
	NONE,
	Debevec,
	Mertens,
};

enum class Tonemap {
	NONE,
	Drago,
};

class Pipeline {
public:
	Align align = Align::NONE;
	Merge merge = Merge::NONE;
	Tonemap tonemap = Tonemap::NONE;
};


#endif //QTHDR_PIPELINE_HPP
