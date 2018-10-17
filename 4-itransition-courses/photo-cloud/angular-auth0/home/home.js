var app = angular.module('sample.home', [
    'auth0',
    'ui.bootstrap',
    'ngFileUpload',
    'ngResource',
    'cloudinary',
    'ngAnimate'
])

app.service('sharedSlides', function () {
    var slides = [];
    var currIndex = 0;

    return {
        getSlides: function () {
            return slides;
        },
        setSlides: function (value) {
            slides = value;
        },
        getIndex: function () {
            return currIndex;
        },
        setIndex: function (value) {
            currIndex = value;
        }
    };
});

app.run([function () {
}]);

app.controller('HomeCtrl', function HomeController($scope, auth, $http, $location, store) {

    $scope.auth = auth;

    $scope.logout = function () {
        auth.signout();
        store.remove('profile');
        store.remove('token');
        $location.path('/login');
    }

    $scope.generatePdf = function() {
        $http({
            url: 'http://localhost:3000/pdf_generator/create',
            method: 'GET',
            params: {email: auth.profile.email}
        }).then(function successCallback(response) {
            alert("Check your mailbox for pdf with photos!");
        }, function errorCallback(response) {
            alert("Check your mailbox for pdf with photos!");
          //  alert('error: server returned status ' + response.status + ' ' + response.statusName);
        });
    };

});

app.controller('Carousel', function ($scope, $http, cloudinary, sharedSlides) {
    $scope.myInterval = 5000;
    $scope.noWrapSlides = false;
    $scope.active = 0;
    var slides = $scope.slides = [];
    var currIndex = $scope.currIndex = 0;

    $scope.addSlides = function () {
        var url = cloudinary.url($scope.auth.profile.email, {format: 'json', type: 'list'});
        $http.get(url).then(function (response) {
            var obj = response.data.resources;
            if (obj.length <= 0)
                return;
            var url_prefix = 'http://res.cloudinary.com/' + cloudinary.config().cloud_name + '/image/upload/v';
            for (var i = 0; i < obj.length; i++) {
                var ver = obj[i].version;
                var pubid = obj[i].public_id;
                var form = obj[i].format;
                slides.push({
                    image: url_prefix + ver + '/' + pubid + '.' + form,
                    text: "<a onclick='function() { alert() }'>Remove</a>",
                    id: currIndex++
                });
            }
            sharedSlides.setSlides(slides);
            sharedSlides.setIndex(currIndex);
        });
    };

    $scope.addSlides();
});


app.controller('photoUploadCtrl', ['$scope', '$rootScope', '$routeParams', '$location', 'Upload', 'cloudinary', 'sharedSlides',
    /* Uploading with Angular File Upload */
    function ($scope, $rootScope, $routeParams, $location, $upload, cloudinary, sharedSlides) {

        var d = new Date();
        $scope.title = "Image: " + d.getHours() + ":" + d.getMinutes() + ":" + d.getSeconds();
        $scope.uploadFiles = function (files) {
            $scope.files = files;
            if (!$scope.files) return;
            angular.forEach(files, function (file) {
                if (file && !file.$error) {
                    file.upload = $upload.upload({
                        url: "https://api.cloudinary.com/v1_1/" + cloudinary.config().cloud_name + "/upload",
                        data: {
                            upload_preset: cloudinary.config().upload_preset,
                            tags: $scope.auth.profile.email,
                            context: 'photo=' + $scope.title,
                            authorization: undefined,
                            file: file
                        }
                    }).progress(function (e) {
                        file.progress = Math.round((e.loaded * 100.0) / e.total);
                        file.status = "Uploading... " + file.progress + "%";
                    }).success(function (data, status, headers, config) {
                        data.context = {custom: {photo: $scope.title}};
                        file.result = data;
                        var slides = sharedSlides.getSlides();
                        var currIndex = sharedSlides.getIndex();
                        slides.push({
                            image: data.url,
                            text: '<a>Remove</a>',
                            id: currIndex++
                        });
                        $scope.active = 0;
                        sharedSlides.setSlides(slides);
                        sharedSlides.setIndex(currIndex);
                    }).error(function (data, status, headers, config) {
                        file.result = data;
                    });
                }
            });
        };
        //});

        /* Modify the look and fill of the dropzone when files are being dragged over it */
        $scope.dragOverClass = function ($event) {
            var items = $event.dataTransfer.items;
            var hasFile = false;
            if (items != null) {
                for (var i = 0; i < items.length; i++) {
                    if (items[i].kind == 'file') {
                        hasFile = true;
                        break;
                    }
                }
            } else {
                hasFile = true;
            }
            return hasFile ? "dragover" : "dragover-err";
        };
    }]);