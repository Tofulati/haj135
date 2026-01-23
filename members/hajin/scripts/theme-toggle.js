(function () {
  "use strict";

  const STORAGE_KEY = "preferred-theme";
  const THEME_LIGHT = "light";
  const THEME_DARK = "dark";

  function getStoredTheme() {
    return localStorage.getItem(STORAGE_KEY);
  }

  function setStoredTheme(theme) {
    localStorage.setItem(STORAGE_KEY, theme);
  }

  function applyTheme(theme) {
    document.documentElement.style.colorScheme = theme;
    document.documentElement.setAttribute("data-theme", theme);
    updateToggleButtonIcon(theme);
  }

  function updateToggleButtonIcon(theme) {
    const button = document.getElementById("theme-toggle");
    if (!button) return;

    const lightIcon = button.querySelector(".theme-icon-light");
    const darkIcon = button.querySelector(".theme-icon-dark");

    if (lightIcon && darkIcon) {
      if (theme === THEME_DARK) {
        lightIcon.style.display = "block";
        darkIcon.style.display = "none";
      } else {
        lightIcon.style.display = "none";
        darkIcon.style.display = "block";
      }
    }
  }

  function getCurrentTheme() {
    const stored = getStoredTheme();
    if (stored) return stored;

    return window.matchMedia("(prefers-color-scheme: dark)").matches
      ? THEME_DARK
      : THEME_LIGHT;
  }

  function toggleTheme() {
    const current = getCurrentTheme();
    const newTheme = current === THEME_DARK ? THEME_LIGHT : THEME_DARK;
    setStoredTheme(newTheme);
    applyTheme(newTheme);
  }

  function createToggleButton() {
    const button = document.createElement("button");
    button.id = "theme-toggle";
    button.type = "button";
    button.className = "theme-toggle-btn";
    button.setAttribute("aria-label", "Toggle theme");
    button.setAttribute("title", "Toggle light/dark theme");

    // Determine icon path based on page location
    const isSubpage = window.location.pathname.includes("/pages/");
    const iconPath = isSubpage ? "../assets/icons/" : "assets/icons/";

    button.innerHTML = `
      <img src="${iconPath}light-theme-black.svg" alt="Switch to light theme" class="theme-icon-light" width="24" height="24" />
      <img src="${iconPath}dark-theme-black.svg" alt="Switch to dark theme" class="theme-icon-dark" width="24" height="24" />
    `;

    button.addEventListener("click", toggleTheme);

    // Insert before the nav ul
    const nav = document.querySelector("nav.site-frame-header");
    if (nav) {
      const ul = nav.querySelector("ul");
      if (ul) {
        nav.insertBefore(button, ul);
      }
    }

    // Set initial icon visibility based on current theme
    updateToggleButtonIcon(getCurrentTheme());
  }

  function init() {
    const storedTheme = getStoredTheme();
    if (storedTheme) {
      applyTheme(storedTheme);
    } else {
      // Apply system preference initially
      applyTheme(getCurrentTheme());
    }

    // Create the toggle button when DOM is ready
    if (document.readyState === "loading") {
      document.addEventListener("DOMContentLoaded", createToggleButton);
    } else {
      createToggleButton();
    }

    // Listen for system theme changes (if no manual override)
    window
      .matchMedia("(prefers-color-scheme: dark)")
      .addEventListener("change", (e) => {
        if (!getStoredTheme()) {
          applyTheme(e.matches ? THEME_DARK : THEME_LIGHT);
        }
      });
  }

  init();
})();

