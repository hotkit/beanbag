
// The wiki AngularJS controller
function WikiController($location, $http) {
    var self = this;
    if ( !$location.path() )
        $location.path("/").replace();
    console.log($location.path());

    this.editors = {
        "title": false};
    this.meta = {}
    this.page = {}
    this.loadpage = function() {
        $http.get($location.path()).
            success(function(data, status, headers, config) {
                self.page = data[""];
                self.meta.version = headers()["etag"];
            }).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    this.loadpage();
    this.savepage = function() {
        $http.put($location.path(), {"":this.page},
                {headers:{'If-Match': self.meta.version}}).
            success(function(data, status, headers, config) {
                self.editors.title = false;
                self.tab = 'show';
                self.meta.version = headers()["etag"];
            }).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    self.tab = 'show';
}

WikiController.$inject = ['$location', '$http'];
