document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('theme-toggle').addEventListener('click', function() {
    if (document.documentElement.getAttribute('data-bs-theme') === 'dark') {
        document.documentElement.removeAttribute('data-bs-theme');}
    else {
        document.documentElement.setAttribute('data-bs-theme', 'dark');}
    });
});
