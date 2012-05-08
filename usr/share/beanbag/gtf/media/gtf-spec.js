
describe("GTF", function() {
    var $scope, ctrl, $httpBackend;
    beforeEach(angular.mock.inject(function($injector, $controller, $rootScope) {
        $httpBackend = $injector.get('$httpBackend');
        $scope = $rootScope.$new();
        ctrl = $controller(controller, {$scope: $scope});
    }));
    it("initialises", function() {
        expect($scope.letters).toEqual("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        expect($scope.letter1).toEqual("G");
        expect($scope.letter2).toEqual("T");
        expect($scope.letter3).toEqual("F");
    });
    it("choose changes the first letter", function() {
        expect($scope.letter1).toEqual("G");
        $scope.choose(1, 'A');
        expect($scope.letter1).toEqual("A");
    });
    it("tla returns the right result", function() {
        $httpBackend.when("GET", "/GTF").respond([true]);
        expect($scope.tla()).toEqual("GTF");
        expect($scope.definitions).not.toBeDefined();
        $httpBackend.flush();
        expect($scope.definitions).toEqual([true]);
    });
});

