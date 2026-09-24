# CS2_Project

## Branching Strategy
We are using a strict Personal -> Feature -> Main workflow to protect the project.

1. **`main`**: The protected production branch. Always playable. Do NOT push directly here.
2. **`[name]`**: Your personal integration branch (e.g., `mani`). 
3. **`[name]/feature/[feature-name]`**: Your active work branches (e.g., `mani/feature/player-movement`).

**Workflow:**
* Branch off your personal branch to create a feature branch.
* When the feature is done, merge it back into your personal branch locally.
* Open a Pull Request (PR) from your personal branch into `main`.

## File Checkout Protocol (CRITICAL)
Unreal Engine binary files (`.uasset`, `.umap`) **cannot be merged**. If two people edit the same file, one person's work will be overwritten and lost.

To prevent this, we use the Discord `#git-check-out` channel.
* **Before editing a Blueprint or Level:** You MUST post in `#git-check-out` stating what you are touching (e.g., "Checking out BP_PlayerCharacter").
* **When you are done and pushed:** Reply to your own message with "Checked in BP_PlayerCharacter."
* **Personal Maps:** Everyone has their own testing level named `[name]_Map`. Do your isolated testing here.
* **The Main Level:** If you need to edit the main game level, you must explicitly declare this in Discord and wait for confirmation that it is free.
