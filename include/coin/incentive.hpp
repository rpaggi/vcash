/*
 * Copyright (c) 2013-2015 John Connor (BM-NC49AxAjcqVcF5jNPu85Rb8MJ2d9JqZt)
 *
 * This file is part of vanillacoin.
 *
 * vanillacoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COIN_INCENTIVE_HPP
#define COIN_INCENTIVE_HPP

#include <cstdint>
#include <map>
#include <mutex>
#include <vector>

#include <coin/incentive_vote.hpp>
#include <coin/key.hpp>
#include <coin/key_public.hpp>
#include <coin/sha256.hpp>

#include <boost/asio.hpp>

namespace coin {

    /**
     * Implements an incentive mechanism.
     */
    class incentive
    {
        public:
        
            /**
             * The percentage.
             */
            enum { percentage = 1 };
        
            /**
             * Constructor
             */
            incentive();
            
            /**
             * The singleton accessor.
             */
            static incentive & instance();
        
            /**
             * Set the incentive key.
             * @param val The value.
             */
            void set_key(const key & val);
        
            /**
             * The incentive key.
             */
            key & get_key();
        
            /**
             * The incentive_vote's.
             */
            std::map<sha256, incentive_vote> & votes();
        
            /**
             * The winners.
             */
            std::map<std::uint32_t, std::string> & winners();
        
            /**
             * Calculates the score of a incentive_vote's.
             * @param ivote The incentive_vote's.
             */
            std::int16_t calculate_score(const incentive_vote & ivote);
        
            /**
             * Calculates the score of a incentive_vote's.
             * @param ep The boost::asio::ip::tcp::endpoint.
             */
            std::int16_t calculate_score(
                const boost::asio::ip::tcp::endpoint & ep
            );
        
            /**
             * Signs
             * @param hash_value The hash of the value.
             * @param signature The signature.
             */
            bool sign(
                const sha256 & hash_value,
                std::vector<std::uint8_t> & signature
            );

            /**
             * Verifies
             * @param public_key The public key.
             * @param hash_value The hash of the value.
             * @param signature The signature.
             */
            bool verify(
                const key_public & public_key,
                const sha256 & hash_value,
                const std::vector<std::uint8_t> & signature
            );
        
        private:
        
            /**
             * The incentive key.
             */
            key m_key;
        
            /**
             * The incentive_vote's.
             */
            std::map<sha256, incentive_vote> m_votes;
        
            /**
             * The winners.
             */
            std::map<std::uint32_t, std::string> m_winners;
        
        protected:
        
            /**
             * The std::mutex.
             */
            static std::mutex mutex_;
    };
}

#endif // COIN_INCENTIVE_HPP
