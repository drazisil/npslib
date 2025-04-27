import { NPSLib } from "./npslib";

describe("NPSLib", () => {
    it("should say hello", () => {
        const lib = new NPSLib();
        console.log = jest.fn();
        lib.sayHello();
        expect(console.log).toHaveBeenCalledWith("Hello, from NPSLib!");
    });

    it("should pack data correctly", () => {
        const lib = new NPSLib();
        const buffer = new Uint8Array(10);
        const packcode = "cl";
        const packedSize = lib.pack(buffer, packcode, 42, 0x12345678);
        expect(packedSize).toBe(5);
        expect(buffer[0]).toBe(42);
        expect(buffer[1]).toBe(0x12);
        expect(buffer[2]).toBe(0x34);
        expect(buffer[3]).toBe(0x56);
        expect(buffer[4]).toBe(0x78);
    });

    it("should unpack data correctly", () => {
        const lib = new NPSLib();
        const buffer = new Uint8Array([42, 0x12, 0x34, 0x56, 0x78]);
        const packcode = "cl";
        const args: any[] = [0, 0]; // Explicit placeholders for unpacked values
        console.log("Buffer:", buffer);
        console.log("Packcode:", packcode);
        console.log("Args before unpack:", args);
        const unpackedSize = lib.unpack(buffer, packcode, args);
        expect(unpackedSize).toBe(5);
        expect(args[0]).toBe(42);
        expect(args[1]).toBe(0x12345678);
    });
});