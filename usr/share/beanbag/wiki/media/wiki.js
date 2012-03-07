
function RouteWatcher($route, $location) {
    if ( !$location.path() )
        $location.path("/").replace();
    $route.otherwise({controller:WikiController, template:'/_/page.html'});
}
RouteWatcher.$inject = ['$route', '$location'];

// The wiki AngularJS controller
function WikiController($location, $http) {
    var self = this;

    this.meta = {}
    this.page = {}
    this.loadpage = function() {
        $http.get($location.path()).
            success(function(data, status, headers, config) {
                self.page = data;
                self.meta.version = headers()["etag"];
            }).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    this.loadpage();
    this.savepage = function() {
        $http.put($location.path(), this.page,
                {headers:{'If-Match': self.meta.version}}).
            success(function(data, status, headers, config) {
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



// --- Custom TinyMCE Service --- //
// http://jsfiddle.net/ProLoser/nTzRA/
angular.directive('ui:tinymce', function(expression, config) {
    return function(element) {
        var callback = function() {
            if (this.isDirty()) {
                this.save();
                element.trigger('change');
            }
            return true;
        };
        element.tinymce({
            // Location of TinyMCE script
            script_url: '/_/tinymce/jscripts/tiny_mce/tiny_mce.js',

            // General options
            theme: "advanced",
            plugins: "inlinepopups",

            // Update Textarea and Trigger change event
            onchange_callback: callback,
            handle_event_callback: callback,
        });
    };
});
