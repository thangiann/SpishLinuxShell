# spish — Systems Programming @ Ioannina Shell

A lightweight, step-by-step Linux shell written in C for a Systems Programming university course.

## Requirements

- **OS:** Linux / POSIX-compliant environment (uses `<unistd.h>` for `getcwd` and `chdir`; not compatible with native Windows).
- **Compiler:** `gcc` (or any standard C compiler).

## Build & Run

```bash
gcc spish.c -o spish
./spish
```
When launched, `spish` displays your current working directory followed by the prompt:

```text
/home/user/project:~spish$
```

## Supported Commands

| Command | Description |
| :--- | :--- |
| `pwd` | Prints the current working directory. |
| `cd` | Changes the current working directory to root (`/`). |
| `cd <path>` | Changes the current working directory to `<path>`. |
| `history` | Displays the last 10 executed commands (excludes `history` itself and blank lines). |
| `exit` | Exits the shell cleanly. Pressing `Ctrl+D` (EOF) also exits. |

## Configuration (`.spishrc`)

On startup, `spish` looks for a `.spishrc` file in the current directory to load custom settings. Lines starting with `#` are treated as comments and ignored.

### Available Settings

| Option | Value | Default | Description |
| :--- | :--- | :--- | :--- |
| `prompt` | `<string>` | `spish$` | Customizes the shell prompt text (max 29 characters). |
| `echo` | `on` \| `off` | `off` | Controls whether executed commands are echoed back. |

### Initialize and Open the Container (Windows)

1. Ensure **Docker Desktop** is running in the background.
2. Open the project folder in **VS Code**.
3. Press `Ctrl + Shift + P` to open the Command Palette (or click the **Remote Window** icon in the bottom-left corner).
4. Search for and select **Dev Containers: Reopen in Container**.
   - *Note: If this is the first time setting up the container and you are prompted for a configuration, select the project's `Dockerfile` or `docker-compose.yml`.*
5. Wait for VS Code to build the image and reload. The initial build may take a few minutes.

Once finished, the bottom-left status bar will show the active container name, and pressing `` Ctrl + ` `` will open a Linux shell directly inside the container.
