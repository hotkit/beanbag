
function RouteWatcher($route, $location) {
    if ( !$location.path() )
        $location.path("/").replace();
    $route.otherwise({controller:WikiController, template:'/_/page.html'});
}
RouteWatcher.$inject = ['$route', '$location'];

// The wiki AngularJS controller
function WikiController($location, $http) {
    var self = this;

    this.meta = {};
    this.page = {};
    this.deleted = null;
    this.success = function(data, status, headers, config) {
        self.tab = 'show';
        self.deleted = null;
        self.page = data;
        self.meta.version = headers()["etag"];
    }
    this.loadpage = function() {
        $http.get($location.path()).
            success(self.success).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    this.loadpage();
    this.savepage = function() {
        $http.put($location.path(), self.page,
                {headers:{'If-Match': self.meta.version}}).
            success(self.success).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    this.deletepage = function() {
        $http.delete($location.path(),
                {headers:{'If-Match': self.meta.version}}).
            error(function(data, status, headers, config) {
                if ( status == 410 ) {
                    self.deleted = self.page;
                    self.page = {};
                    self.tab = 'edit';
                    self.meta.version = null;
                } else
                    console.log("error", data, status, headers, config);
            });
    }
    this.undelete = function() {
        $http.put($location.path(), self.deleted,
                  {headers:{'If-Not-Match': '*'}}).
            success(self.success).
            error(function(data, status, headers, config) {
                console.log("error", data, status, headers, config);
            });
    }
    self.tab = 'edit';
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
            plugins: "inlinepopups,preelementfix",

            // Update Textarea and Trigger change event
            onchange_callback: callback,
            handle_event_callback: callback,
        });
    };
});
