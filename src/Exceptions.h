#pragma once

#include <exception>
#include <string>

/**
 * Class for SDL exceptions.
 * Inherited from std::exception.
 */
class SDLError : public std::exception
{
	private:
		std::string message;

	public:
		/**
		 * Constructs new SDLError instance.
		 * @param inMessage Message that describes exception.
		 */
		SDLError(std::string& inMessage) : message(std::move(inMessage)) { }

		/**
		 * Get exception description.
		 * @return Pointer to message, that describes exception.
		 */
		const char * what() const noexcept override { return message.c_str(); }
};

/**
 * Class for TTF exceptions.
 * Inherited from std::exception.
 */
class TTFError : public std::exception
{
private:
		std::string message;

public:
		/**
		 * Constructs new MixError message.
		 * @param inMessage Message that describes exception.
		 */
		TTFError(std::string& inMessage) : message(std::move(inMessage)) { }

		/**
		 * Get exception description.
		 * @return Pointer to message, that describes exception.
		 */
		const char * what() const noexcept override { return message.c_str(); }
};

/**
 * Class for MIX exceptions.
 * Inherited from std::exception.
 */
class MixError : public std::exception
{
	private:
		std::string message;

	public:
		/**
		 * Constructs new MixError message.
		 * @param inMessage Message that describes exception.
		 */
		MixError(std::string& inMessage) : message(std::move(inMessage)) { }

		/**
		 * Get exception description.
		 * @return Pointer to message, that describes exception.
		 */
		const char * what() const noexcept override { return message.c_str(); }
};

/**
 * Class for exception, when handling with files.
 * Inherited from std::exception.
 */
class FileError : public std::exception
{
	private:
		std::string message;

	public:
		/**
		 * Constructs new MixError message.
		 * @param inMessage Message that describes exception.
		 */
		FileError(std::string& inMessage) : message(std::move(inMessage)) { }

		/**
		 * Get exception description.
		 * @return Pointer to message, that describes exception.
		 */
		const char * what() const noexcept override { return message.c_str(); }
};

/**
 * Class for game core exception.
 * Inherited from std::exception.
 */
class GameError : public std::exception
{
	private:
		std::string message;

	public:
		/**
		 * Constructs new MixError message.
		 * @param inMessage Message that describes exception.
		 */
		GameError(std::string& inMessage) : message(std::move(inMessage)) { }

		/**
		 * Get exception description.
		 * @return Pointer to message, that describes exception.
		 */
		const char * what() const noexcept override { return message.c_str(); }
};