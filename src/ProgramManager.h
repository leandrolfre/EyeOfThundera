#pragma once

#include <unordered_map>
#include <memory>

struct Shader;
class Program;

using ProgramUPtr = std::unique_ptr<Program>;

class ProgramManager
{
public:
	static ProgramManager& getInstance();
	void addProgram(ProgramUPtr program, const std::string& key);
	Program* getProgram(const std::string& key);
private:
	ProgramManager() = default;
private:
	std::unordered_map<std::string, ProgramUPtr> _programCache;