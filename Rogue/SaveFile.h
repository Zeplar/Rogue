#pragma once
class SaveFile
{
public:
	SaveFile(const std::string& fileName);
	static void loadFile(const std::string & fileName);
	~SaveFile();
	static bool saveExists(const std::string& filename);
};

