//
//  DustEffectView.swift
//  SwiftDemo
//
//  Created by dzcx on 2019/8/16.
//  Copyright © 2019 dzcx. All rights reserved.
//

import UIKit

class DustEffectView: UIView {
    
    override init(frame: CGRect) {
        super.init(frame: frame)
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
    }

    private func createDustImages(image: UIImage) -> [UIImage] {
        var images = [UIImage]()
        guard let inputCGImage = image.cgImage else { return images }
        
        
        
        return images
    }
}