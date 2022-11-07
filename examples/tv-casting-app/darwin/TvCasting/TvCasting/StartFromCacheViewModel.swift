/*
 * SPDX-FileCopyrightText: (c) 2020-2022 Project CHIP Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import Foundation
import os.log

class StartFromCacheViewModel: ObservableObject {
    let Log = Logger(subsystem: "com.matter.casting",
                     category: "StartFromCacheViewModel")
    
    @Published var videoPlayers: [VideoPlayer] = []
        
    func readFromCache() {
        if let castingServerBridge = CastingServerBridge.getSharedInstance()
        {
            castingServerBridge.readCachedVideoPlayers(DispatchQueue.main, readCachedVideoPlayersHandler: { (cachedVideoPlayers: NSMutableArray?) -> () in
                if(cachedVideoPlayers != nil)
                {
                    self.videoPlayers = cachedVideoPlayers! as! [VideoPlayer]
                }
            })
        }
    }
}
