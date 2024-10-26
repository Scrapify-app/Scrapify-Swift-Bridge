// Swift module 'Example'

import Foundation
import AppKit

extension NSImage {
    func toBase64(resizedTo newSize: NSSize = NSSize(width: 256, height: 256)) -> String? {
        let cgImgRef = self.cgImage(forProposedRect: nil, context: nil, hints: nil)
        let bmpImgRef = NSBitmapImageRep(cgImage: cgImgRef!)
        let data = bmpImgRef.representation(
            using: NSBitmapImageRep.FileType.png,
            properties: [:]
        )!

        return "data:image/png;base64,\(data.base64EncodedString())"
    }
}

public func searchProcessIconByPid(processId: Int32) -> String? {
    let process = NSRunningApplication(processIdentifier: processId)
    return process?.icon?.toBase64()
}
