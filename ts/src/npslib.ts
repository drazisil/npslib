export class NPSLib {
    // Example method to mimic the say_hello functionality
    sayHello(): void {
        console.log("Hello, from NPSLib!");
    }

    // Example pack method
    pack(buffer: Uint8Array, packcode: string, ...args: any[]): number {
        let index = 0;

        for (const code of packcode) {
            switch (code) {
                case 'b': {
                    const data = args.shift();
                    if (!(data instanceof Uint8Array)) {
                        throw new Error("Invalid data for 'b'");
                    }
                    buffer.set(data, index);
                    index += data.length;
                    break;
                }
                case 'c': {
                    const byte = args.shift();
                    if (typeof byte !== 'number') {
                        throw new Error("Invalid data for 'c'");
                    }
                    buffer[index++] = byte;
                    break;
                }
                case 'l': {
                    const value = args.shift();
                    if (typeof value !== 'number') {
                        throw new Error("Invalid data for 'l'");
                    }
                    buffer[index++] = (value >> 24) & 0xff;
                    buffer[index++] = (value >> 16) & 0xff;
                    buffer[index++] = (value >> 8) & 0xff;
                    buffer[index++] = value & 0xff;
                    break;
                }
                default:
                    throw new Error(`Unsupported packcode: ${code}`);
            }
        }

        return index;
    }

    // Example unpack method
    unpack(buffer: Uint8Array, packcode: string, args: any[]): number {
        let index = 0;
        let argIndex = 0; // Reset argIndex to ensure proper indexing

        for (const code of packcode) {
            console.log(`Processing code: ${code}, Index: ${index}, ArgIndex: ${argIndex}, Args Before: ${JSON.stringify(args)}`);
            switch (code) {
                case 'b': {
                    const length = args[argIndex];
                    if (typeof length !== 'number') {
                        throw new Error("Invalid length for 'b'");
                    }
                    const data = buffer.slice(index, index + length);
                    args[argIndex] = data; // Ensure the correct index is updated
                    console.log(`Updated Args: ${JSON.stringify(args)}`);
                    index += length;
                    break;
                }
                case 'c': {
                    const byte = buffer[index++];
                    console.log(`Unpacking byte: ${byte}, updating args[${argIndex}]`);
                    args[argIndex] = byte; // Correctly assign the unpacked byte
                    console.log(`Updated Args: ${JSON.stringify(args)}`);
                    break;
                }
                case 'l': {
                    const value = (buffer[index++] << 24) |
                                  (buffer[index++] << 16) |
                                  (buffer[index++] << 8) |
                                  buffer[index++];
                    console.log(`Unpacking value: ${value}, updating args[${argIndex}]`);
                    args[argIndex] = value;
                    console.log(`Updated Args: ${JSON.stringify(args)}`);
                    break;
                }
                default:
                    throw new Error(`Unsupported packcode: ${code}`);
            }
            console.log(`Args After: ${JSON.stringify(args)}`);
            argIndex++;
        }

        return index;
    }
}