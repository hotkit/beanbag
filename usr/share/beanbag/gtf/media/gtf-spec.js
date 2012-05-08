
describe("GTF", function() {
    it("initialises", function() {
        var scope = {}, http = {};
        var ctrl = new controller(scope, http);
        expect(scope.letters).toEqual("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    });
});

