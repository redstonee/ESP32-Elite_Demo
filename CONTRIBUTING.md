# Contributing to ESP32-Elite Demo

Thank you for your interest in contributing to the ESP32-Elite Demo project! This document provides guidelines for contributing to this repository.

## How to Contribute

### Reporting Issues

If you find a bug or have a suggestion for improvement:

1. Check if the issue already exists in the Issues section
2. If not, create a new issue with a clear description
3. Include steps to reproduce (for bugs)
4. Include expected vs actual behavior

### Contributing Code

1. Fork the repository
2. Create a new branch for your feature or bug fix
3. Make your changes following the coding standards below
4. Test your changes thoroughly
5. Submit a pull request with a clear description of your changes

### Adding New Demos

If you want to add a new demo project:

1. Create a new directory with a descriptive name
2. Follow the existing project structure:
   - `.gitignore` - Use the same pattern as other demos
   - `.vscode/` - VSCode settings
   - `platformio.ini` - PlatformIO configuration
   - `src/main.cpp` - Your demo code
   - `include/`, `lib/`, `test/` - Standard directories
3. Update the README.md to include your new demo in the list
4. Update the README_zh.md with the Chinese translation
5. Add clear comments in your code explaining what it does
6. Test on actual ESP32-Elite hardware if possible

## Coding Standards

- Use meaningful variable and function names
- Add comments to explain complex logic
- Follow the existing code style in the repository
- Keep demo code simple and educational
- Include Serial.print statements to help users understand what's happening

## Demo Requirements

Each demo should:
- Have a clear educational purpose
- Work with the ESP32-Elite board hardware
- Include helpful Serial output for debugging
- Be documented in both README files (English and Chinese)
- Follow the PlatformIO project structure

## Testing

Before submitting:
- Build your code successfully with PlatformIO
- Test on ESP32-Elite hardware if available
- Verify Serial output is helpful and informative
- Check that your demo doesn't interfere with other demos

## Questions?

If you have questions about contributing, feel free to open an issue for discussion.

Thank you for helping make this project better!
