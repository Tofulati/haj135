/**
 * client-side validation and submission handling for the contact form.
 */

(function () {
  "use strict";

  const validationRules = {
    name: {
      required: true,
      minLength: 2,
      maxLength: 100,
      pattern: /^[a-zA-Z\s'-]+$/,
      messages: {
        required: "Please enter your name.",
        minLength: "Name must be at least 2 characters.",
        maxLength: "Name must be less than 100 characters.",
        pattern: "Name can only contain letters, spaces, hyphens, and apostrophes.",
      },
    },
    email: {
      required: true,
      pattern: /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
      messages: {
        required: "Please enter your email address.",
        pattern: "Please enter a valid email address.",
      },
    },
    subject: {
      required: true,
      minLength: 3,
      maxLength: 200,
      messages: {
        required: "Please enter a subject.",
        minLength: "Subject must be at least 3 characters.",
        maxLength: "Subject must be less than 200 characters.",
      },
    },
    message: {
      required: true,
      minLength: 10,
      maxLength: 2000,
      messages: {
        required: "Please enter your message.",
        minLength: "Message must be at least 10 characters.",
        maxLength: "Message must be less than 2000 characters.",
      },
    },
  };

  function validateField(fieldName, value) {
    const rules = validationRules[fieldName];
    if (!rules) return null;

    const trimmedValue = value.trim();

    if (rules.required && !trimmedValue) {
      return rules.messages.required;
    }

    if (trimmedValue && rules.minLength && trimmedValue.length < rules.minLength) {
      return rules.messages.minLength;
    }

    if (trimmedValue && rules.maxLength && trimmedValue.length > rules.maxLength) {
      return rules.messages.maxLength;
    }

    if (trimmedValue && rules.pattern && !rules.pattern.test(trimmedValue)) {
      return rules.messages.pattern;
    }

    return null;
  }

  function showError(field, message) {
    clearError(field);
    field.classList.add("field-error");
    field.setAttribute("aria-invalid", "true");

    const errorEl = document.createElement("span");
    errorEl.className = "error-message";
    errorEl.setAttribute("role", "alert");
    errorEl.textContent = message;
    field.parentNode.appendChild(errorEl);
  }

  function clearError(field) {
    field.classList.remove("field-error");
    field.removeAttribute("aria-invalid");
    const errorEl = field.parentNode.querySelector(".error-message");
    if (errorEl) errorEl.remove();
  }

  function handleSubmit(event) {
    const form = event.target;
    let isValid = true;

    // Validate all fields
    Object.keys(validationRules).forEach((fieldName) => {
      const field = form.querySelector(`#${fieldName}`);
      if (field) {
        const error = validateField(fieldName, field.value);
        if (error) {
          showError(field, error);
          isValid = false;
        } else {
          clearError(field);
        }
      }
    });

    // Only prevent submission if validation fails
    if (!isValid) {
      event.preventDefault();
    }
    // If valid, allow form to submit to Formspree
  }

  function handleBlur(event) {
    const field = event.target;
    const fieldName = field.id;

    if (validationRules[fieldName]) {
      const error = validateField(fieldName, field.value);
      if (error) {
        showError(field, error);
      } else {
        clearError(field);
      }
    }
  }

  function init() {
    const form = document.querySelector(".contact-form");
    if (!form) return;

    form.addEventListener("submit", handleSubmit);

    // Add blur validation for each field
    Object.keys(validationRules).forEach((fieldName) => {
      const field = form.querySelector(`#${fieldName}`);
      if (field) {
        field.addEventListener("blur", handleBlur);
        // Clear errors on input
        field.addEventListener("input", () => clearError(field));
      }
    });
  }

  // Initialize when DOM is ready
  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", init);
  } else {
    init();
  }
})();

