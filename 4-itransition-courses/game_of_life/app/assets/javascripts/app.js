angular.module('GameOfLife', ['ui.bootstrap'])
    .controller('LifeCtrl', ['$scope', '$http', '$window',
        function ($scope, $http, $window) {

            $scope.isCollapsed = true;

            String.prototype.replaceAt=function(index, character) {
                return this.substr(0, index) + character + this.substr(index+character.length);
            }

            angular.element($window).bind('resize', function() {
                var canvas = document.getElementById('cells');
                $scope.width = Math.min( Math.floor(window.innerWidth * 0.9 / $scope.w) * $scope.w,
                                            $scope.cols * $scope.w);
                $scope.height = Math.min( Math.floor(window.innerHeight * 0.7 / $scope.w) * $scope.w,
                                            $scope.rows * $scope.w);
                canvas.setAttribute('width', $scope.width.toString() );
                canvas.setAttribute('height', $scope.height.toString() );
                $scope.fillCells();
            });

            $scope.w = 20;
            $scope.cols = 80;
            $scope.rows = 32;

            $scope.state = '';
            $scope.source = 'server';
            $scope.numberOfGenerations = 1;
            $scope.currentGeneration = 1;

            $scope.width = Math.floor(window.innerWidth * 0.9 / $scope.w) * $scope.w;
            $scope.height = Math.floor(window.innerHeight * 0.7 / $scope.w) * $scope.w;

            var canvas = document.getElementById('cells');

            canvas.setAttribute('width', $scope.width.toString() );
            canvas.setAttribute('height', $scope.height.toString() );

            canvas.addEventListener('click', function (event) {
                var x = event.pageX - canvas.offsetLeft,
                    y = event.pageY - canvas.offsetTop,
                    w = $scope.w;
                x = Math.floor(x/w);
                y = Math.floor(y/w);
                var cell = $scope.state.charAt(y*$scope.cols+x);
                if (cell == ".") {
                    $scope.state = $scope.state.replaceAt(y*$scope.cols+x, "O");
                } else {
                    $scope.state = $scope.state.replaceAt(y*$scope.cols+x, ".");
                }
                $scope.source = 'client';
                $scope.fillCells();
            });

            drawField();
            addRedRect();
            clearStateVar();

            function drawField() {
                var canvas = document.getElementById('cells');
                var context = canvas.getContext('2d');
                context.beginPath();
                var w = $scope.w;
                for (var i = w; i < $scope.width; i += w) {
                    context.moveTo(i + 0.5, 0);
                    context.lineTo(i + 0.5, $scope.height);
                }
                for (var j = w; j < $scope.height; j += w) {
                    context.moveTo(0, j + 0.5);
                    context.lineTo($scope.width, j + 0.5);
                }
                context.stroke();
            }

            $scope.fillCells = function() {
                var canvas = document.getElementById('cells');
                var context = canvas.getContext('2d');
                context.strokeStyle = 'black';
                context.clearRect(0,0,canvas.width,canvas.height);
                drawField();
                var w = $scope.w;
                context.beginPath();
                for (var i=0; i<$scope.state.length; i++) {
                    if ($scope.state[i] == 'O') {
                        context.fillRect(i%$scope.cols * w, Math.floor(i/$scope.cols) * w, w, w);
                    }
                }
                context.stroke();
                addRedRect();
            }

            function addRedRect() {
                var canvas = document.getElementById('cells');
                var context = canvas.getContext('2d');
                var w = $scope.w;
                context.beginPath();
                context.strokeStyle = 'red';
                context.rect(2,2,w-4,w-4);
                context.stroke();
            }

            function clearStateVar() {
                $scope.state = "";
                for (var i = 0; i<$scope.rows * $scope.cols; i++)
                    $scope.state += "."
            }

            $scope.countState = function() {
                var stateToSend = "NO";
                if ($scope.source == 'client')
                    stateToSend = makeStateShorter();
                $http({
                    url: 'http://localhost:3000/life/count',
                    method: 'GET',
                    params: {
                        steps: $scope.numberOfGenerations,
                        client_state: stateToSend,
                        source: $scope.source
                    }
                }).then(function successCallback(response) {
                    $scope.state = response.data.new_state;
                    $scope.currentGeneration = response.data.generation;
                    $scope.source = 'server';
                    $scope.fillCells();
                }, function errorCallback(response) {
                    alert("error");
                });
            }

            function makeStateShorter() {
                var short = '';
                var state = $scope.state;
                for (var i=0; i<$scope.cols*$scope.rows; i+=2) {
                    if (state[i]=='.' && state[i+1]=='.')
                        short += 'A';
                    else if (state[i]=='O' && state[i+1]=='.')
                        short += 'B';
                    else if (state[i]=='.' && state[i+1]=='O')
                        short += 'C';
                    else if (state[i]=='O' && state[i+1]=='O')
                        short += 'D';
                }
                return short;
            }

            $scope.clearClient = function() {
                clearStateVar();
                $scope.fillCells();
                $scope.source = 'server';
                $scope.numberOfGenerations = 1;
                $scope.currentGeneration = 1;
            }

            $scope.requestState = function(type) {
                $http({
                    url: 'http://localhost:3000/life/init_state',
                    method: 'GET',
                    params: {
                        type: type
                    }
                }).then(function successCallback(response) {
                    $scope.state = response.data.new_state;
                    $scope.currentGeneration = response.data.generation;
                    $scope.source = 'server';
                    $scope.fillCells();
                }, function errorCallback(response) {
                    alert("error");
                });
            }

            $scope.clearServer = function () {
                $http({
                    url: 'http://localhost:3000/life/clear_state',
                    method: 'GET'
                }).then(function successCallback(response) {
                    if (response.data.success == '1') {
                        $scope.clearClient();
                    }
                }, function errorCallback(response) {
                    alert("error");
                });
            }

        }

    ]);