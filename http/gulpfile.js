var gulp        = require('gulp');
var browserSync = require('browser-sync').create();

// Static server
// gulp.task('browser-sync', function() {
//     browserSync.init({
//         server: {
//             baseDir: "./"
//         }
//     });
// });

gulp.task('browser-sync', function() {
    browserSync.init({
    	proxy: "localhost"
    });
});

gulp.task('watch', ['browser-sync'], function () {
    gulp.watch("*.html").on('change', browserSync.reload);
    gulp.watch("css/*.css").on('change', browserSync.reload);
    gulp.watch("*.php").on('change', browserSync.reload);
});