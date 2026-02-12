# Minishell Implementation

This is a comprehensive implementation of a shell program (minishell) that meets all the mandatory requirements as specified.

## Project Structure

```
.
├── Makefile              # Build configuration with proper flags
├── minishell.h          # Header with all structures and prototypes
├── main.c               # Main loop and initialization
├── lexer.c              # Tokenization of input
├── parser.c             # Command parsing and AST building
├── built_ins.c          # Built-in commands (echo, pwd, env)
├── built_ins2.c         # More built-ins (cd, export, unset, exit)
├── executor.c           # Command execution and pipeline handling
├── env_utils.c          # Environment variable management
├── signals.c            # Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
├── redirections.c       # Input/output redirections and heredoc
├── pipes.c              # String utilities and variable expansion
├── utils.c              # Basic string utilities
└── test_minishell.sh    # Testing script
```

## Compliance with Requirements

### ✅ Compilation Requirements
- **Makefile with proper flags**: Uses `-Wall -Wextra -Werror`
- **No compilation errors**: Clean compilation
- **No re-linking**: Makefile correctly tracks dependencies

### ✅ Simple Commands & Global Variables
- **Absolute path execution**: Supports `/bin/ls`, `/usr/bin/env`, etc.
- **Global variable limit**: Only `g_signal_received` for signal handling
- **Empty commands**: Properly handled
- **Spaces/tabs only**: Correctly ignored

### ✅ Arguments
- **Command arguments**: Full support for command-line arguments
- **Multiple commands**: Tested with various commands and arguments

### ✅ Built-in Commands
- **echo**: With and without `-n` option
- **cd**: With relative paths, absolute paths, `~`, `.`, `..`, and `-`
- **pwd**: Current working directory
- **export**: Environment variable creation and modification
- **unset**: Environment variable removal
- **env**: Display all environment variables
- **exit**: With optional exit codes and error handling

### ✅ Return Value Handling
- **Exit status tracking**: `$?` variable properly maintained
- **Command success/failure**: Return values correctly propagated
- **Error handling**: Invalid commands return appropriate exit codes

### ✅ Signal Handling
- **Ctrl+C**: New line with new prompt (empty or with input)
- **Ctrl+\\**: Ignored in interactive mode
- **Ctrl+D**: Exit shell when prompt is empty
- **Process signals**: Proper handling during command execution

### ✅ Quote Handling
- **Double quotes**: Variable expansion inside quotes
- **Single quotes**: Literal interpretation, no expansion
- **Whitespace preservation**: Correctly handled within quotes

### ✅ Environment Variables
- **Variable expansion**: `$VAR` and `${VAR}` syntax
- **Special variables**: `$?` for exit status
- **Quote context**: Expansion in double quotes, literal in single quotes

### ✅ Redirections
- **Input redirection**: `< file`
- **Output redirection**: `> file`
- **Append redirection**: `>> file`
- **Here document**: `<< delimiter`
- **Multiple redirections**: Chaining and combination support

### ✅ Pipes
- **Pipeline execution**: `cmd1 | cmd2 | cmd3`
- **Error propagation**: Failed commands in pipeline
- **Mixed operations**: Pipes with redirections

### ✅ Path Resolution
- **Relative paths**: Support for `./command`, `../bin/ls`
- **PATH environment**: Command lookup in PATH directories
- **PATH manipulation**: Works when PATH is modified or unset

## Key Implementation Details

### Signal Management
- Uses only one global variable (`g_signal_received`) for signal status
- Proper signal handling without interfering with child processes
- Readline integration for clean prompt management

### Memory Management
- All allocations properly tracked and freed
- No memory leaks in normal operation
- Proper cleanup on exit

### Error Handling
- Comprehensive error checking for system calls
- Appropriate error messages matching bash behavior
- Graceful handling of edge cases

### Process Management
- Proper forking and waiting for child processes
- Pipeline process coordination
- Signal propagation to child processes

## Testing Compliance

The implementation passes all the mandatory requirements:

1. **Compilation**: Clean build with required flags
2. **Basic functionality**: Simple commands work correctly
3. **Built-ins**: All required built-in commands implemented
4. **Environment**: Variable handling and manipulation
5. **Quotes**: Proper single and double quote processing
6. **Redirections**: All redirection types supported
7. **Pipes**: Pipeline execution with proper error handling
8. **Signals**: Correct interactive signal behavior
9. **Edge cases**: Empty input, whitespace, malformed commands

## Usage Examples

```bash
# Run the minishell
./minishell

# Basic commands
/bin/ls -la
echo "Hello, World!"
pwd

# Environment variables
export TEST=value
echo $TEST
unset TEST

# Pipes and redirections
ls | grep minishell
echo "test" > output.txt
cat < output.txt
cat << EOF
heredoc content
EOF

# Built-in commands
cd /tmp
pwd
exit 0
```

This implementation provides a fully functional shell that meets all the mandatory requirements for the minishell project.
