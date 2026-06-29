# GitHub Upload Guide

## Before Uploading

Update these items:

- Confirm that the `LICENSE` file uses your preferred public name.
- Add real project photos inside `images/`.
- Add a circuit diagram as `images/circuit-diagram.png`.
- Add your final GitHub repository link to your resume.

## Recommended Repository Name

Use a clear name such as:

```text
ESP32-Flood-Weather-Monitoring-System
```

## Suggested Commit History

Instead of uploading everything as one commit, use meaningful commits:

```bash
git add README.md LICENSE .gitignore
git commit -m "Add project documentation"

git add firmware/FloodGuardMonitor
git commit -m "Add modular ESP32 flood monitoring firmware"

git add docs images
git commit -m "Add pinout, flowchart, and portfolio docs"
```

## Upload Commands

From inside this project folder:

```bash
git init
git add .
git commit -m "Initial ESP32 flood monitoring project"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/ESP32-Flood-Weather-Monitoring-System.git
git push -u origin main
```

Create the empty repository on GitHub first, then replace `YOUR_USERNAME` with your GitHub username.

## GitHub Profile Tips

- Pin this repository on your GitHub profile.
- Add a clean profile README with your skills: Embedded C, C++, ESP32, Arduino, I2C, SPI, UART, sensors, data logging.
- Add photos and diagrams to make the project visual.
- Write your README so a recruiter understands the project in under one minute.
- Keep commit messages professional and specific.
- Add at least three more embedded projects over time: one communication project, one RTOS project, and one motor/control project.
