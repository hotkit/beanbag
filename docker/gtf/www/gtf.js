
function controller($scope, $http) {
    $scope.letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    $scope.letter1 = 'G';
    $scope.letter2 = 'T';
    $scope.letter3 = 'F';

    $scope.choose = function(n, c) { $scope['letter' + n] = c; }

    $scope.old_tla = null;
    $scope.tla = function() {
        var new_tla = $scope.letter1 + $scope.letter2 + $scope.letter3;
        if ( new_tla != $scope.old_tla ) {
            $scope.old_tla = new_tla;
            $http.get('/'+ new_tla).
                success(function(data) {
                    $scope.definitions = data;
                }).
                error(function() {
                    $scope.definitions = [];
                    $scope.wikipedia = null;
                    $http.jsonp('http://en.wikipedia.org/w/api.php?' +
                            'format=json&action=query&list=search&' +
                            'srsearch=' + new_tla + '&callback=JSON_CALLBACK').
                        success(function(data) {
                            $scope.wikipedia = data;
                        }).
                        error(function() {
                            $scope.wikipedia = {error:{info:"Could not contact Wikipedia"}};
                        });
                });
        }
        return new_tla;
    }
}

