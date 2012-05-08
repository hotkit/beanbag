
describe("GTF", function() {
    it("initialises", function() {
        var scope = {}, http = {};
        var ctrl = new controller(scope, http);
        expect(scope.letters).toEqual("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        expect(scope.letter1).toEqual("G");
        expect(scope.letter2).toEqual("T");
        expect(scope.letter3).toEqual("F");
    });
});

