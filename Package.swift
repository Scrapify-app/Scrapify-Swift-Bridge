// swift-tools-version:6.0
import PackageDescription

let package = Package(
    name: "SwiftBridge",
    platforms: [.macOS(.v15)],
    products: [
        .library(name: "SwiftBridge", type: .static, targets: ["SwiftBridge"]),
    ],
    targets: [
        .target(name: "SwiftBridge", dependencies: []),
    ]
)
