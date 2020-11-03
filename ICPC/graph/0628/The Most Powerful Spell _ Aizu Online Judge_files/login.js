// Login Form

$(function() {
    var button = $('#login');
    var box = $('#loginBox');
    var form = $('#loginForm');

    button.mouseup(function(login) {
        box.toggle();
        button.toggleClass('active');
    });
    form.mouseup(function() { 
        return false;
    });
    $(this).mouseup(function(login) {
        if(!($(login.target).parent('#login').length > 0)) {
            button.removeClass('active');
            box.hide();
        }
    });
});

$(function() {
    var button = $('#register');
    var box = $('#registerBox');
    var form = $('#registerForm');

    button.mouseup(function(register) {
        box.toggle();
        button.toggleClass('active');
    });
    form.mouseup(function() { 
        return false;
    });
    $(this).mouseup(function(register) {
        if(!($(register.target).parent('#register').length > 0)) {
            button.removeClass('active');
            box.hide();
        }
    });
});

