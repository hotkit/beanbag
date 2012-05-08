
describe("GTF", function() {
    var scope, http, ctrl;
    beforeEach(function() {
        scope = {};
        http = {};
        ctrl = new controller(scope, http);
    });
    it("initialises", function() {
        expect(scope.letters).toEqual("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        expect(scope.letter1).toEqual("G");
        expect(scope.letter2).toEqual("T");
        expect(scope.letter3).toEqual("F");
    });
    it("choose changes the first letter", function() {
        expect(scope.letter1).toEqual("G");
        scope.choose(1, 'A');
        expect(scope.letter1).toEqual("A");
    });
});

