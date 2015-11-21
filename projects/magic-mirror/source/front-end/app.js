$(function () {
    var socket = window.socket = io.connect(document.location.origin),
        timeout = null,
        width = '80%';

    function hide() {
        $(".start").css('opacity', '0');
        $(".process").css('opacity', '0');
        $(".result").css('opacity', '0');
        $(".listen").css('opacity', '0');
        $(".listen").css('width', '0%');
        $(".error").hide();

        clearTimeout(timeout);
    }

    function listening() {
        $(".start").css('opacity', '0');
        $(".process").css('opacity', '0');
        $(".result").css('opacity', '0');
        $(".listen").css('opacity', '100');
        $(".listen").css('width', width);
        $(".error").hide();

        clearTimeout(timeout);
        timeout = setTimeout(hide, 30000);
    }

    function processing() {
        $(".start").css('opacity', '0');
        $(".process").css('opacity', '100');
        $(".result").css('opacity', '0');
        $(".listen").css('opacity', '0');
        $(".listen").css('width', '0%');
        $(".error").hide();

        clearTimeout(timeout);
        timeout = setTimeout(hide, 30000);
    }

    function speech(text, isHtml) {
        $(".start").css('opacity', '0');
        $(".process").css('opacity', '0');
        $(".result").css('opacity', '100');
        $(".listen").css('opacity', '0');
        $(".listen").css('width', '0%');
        $(".error").hide();

        if (isHtml) $(".result").html(text);
        if (!isHtml) $(".result").text(text);

        clearTimeout(timeout);
        timeout = setTimeout(hide, 60000);
    }

    function error() {
        $(".start").css('opacity', '0');
        $(".process").css('opacity', '0');
        $(".result").css('opacity', '0');
        $(".listen").css('opacity', '0');
        $(".listen").css('width', '0%');
        $(".error").show();

        clearTimeout(timeout);
        timeout = setTimeout(hide, 5000);
    }

    socket.on('recording', listening);
    socket.on('processing', processing);
    socket.on('speech', speech);
    socket.on('problem', error);
});
