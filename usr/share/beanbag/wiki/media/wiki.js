
// The wiki AngularJS controller
function WikiController($location, $http) {
    var self = this;
    if ( !$location.path() )
        $location.path("/").replace();
    console.log($location.path());

    this.editors = {
        "title": false,
    };
    this.loadpage = function() {
        $http({method:"GET", url: $location.path()}).
            success(function(data, status, headers, config) {
                self.page = data[""];
                self.version = headers()["etag"];
            }).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    this.loadpage();
}

WikiController.$inject = ['$location', '$http'];
