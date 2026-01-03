# Contributing to ESP32-Elite Demo

Thank you for your interest in contributing to the ESP32-Elite Demo project! This document provides guidelines for contributing to this repository.

## How to Contribute

### Reporting Issues

If you find a bug or have a suggestion for improvement:

1. Check if the issue already exists in the [Issues](https://github.com/redstonee/ESP32-Elite_Demo/issues) section
2. If not, create a new issue with a clear title and description
3. Include steps to reproduce the problem (if applicable)
4. Mention the hardware/software versions you're using

### Submitting Changes

1. **Fork the Repository**
   - Fork the repository to your GitHub account
   - Clone your fork locally

2. **Create a Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make Your Changes**
   - Follow the existing code style and structure
   - Test your changes thoroughly with the ESP32-Elite board
   - Ensure your demo works as expected

4. **Commit Your Changes**
   - Write clear, concise commit messages
   - Reference any related issues in your commit messages

5. **Push and Create a Pull Request**
   - Push your changes to your fork
   - Create a pull request to the main repository
   - Provide a clear description of your changes

## Adding New Demos

When adding a new demo:

1. Create a new directory following the naming convention of existing demos
2. Include a `platformio.ini` file with appropriate configuration
3. Add your source code in the `src/` directory
4. Update the main `README.md` to include your demo in the "Available Demos" section
5. Include comments in your code to explain what it does
6. Test thoroughly on the ESP32-Elite board

## Code Style

- Use consistent indentation (follow existing demos)
- Add comments to explain complex logic
- Keep code readable and maintainable
- Follow C/C++ best practices for embedded systems

## Testing

- Test all changes on actual ESP32-Elite hardware
- Verify that existing demos still work after your changes
- Document any hardware requirements or setup needed

## Questions?

If you have questions about contributing, feel free to open an issue for discussion.

Thank you for helping make ESP32-Elite Demo better!
